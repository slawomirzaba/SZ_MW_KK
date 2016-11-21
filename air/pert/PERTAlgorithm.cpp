#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cmath>

struct Time
{
	int optimistic;
	int possible;
	int pessimistic;

	Time()
	: optimistic( 0 )
	, possible( 0 )
	, pessimistic( 0 )
	{
	}
};

struct Task
{
	int id;
	int earlyStart;
	int earlyFinish;
	int lateStart;
	int lateFinish;
	int totalFloat;
	bool isCritical;
	bool visited;
	double duration;
	double variance;
	Time timeTrio;
	std::vector<int> predecessors;
	std::vector<int> successors;

	Task()
	: id( 0 )
	, earlyStart( 0 )
	, earlyFinish( 0 )
	, lateStart( 0 )
	, lateFinish( 0 )
	, totalFloat( -1 )
	, isCritical( false )
	, visited( false )
	, duration( 0.0 )
	, variance( 0.0 )
	, timeTrio()
	{
		predecessors.clear();
		successors.clear();
	}

	bool operator < ( const Task& task ) const
	{
		return lateFinish < task.lateFinish;
	}
};

struct Connection
{
	int from;
	int to;

	Connection() : from( -1 ), to( -1 ) {}
};

int earliestStart = 0;
int earliestFinish = 0;
int latestStart = 0;
int latestFinish = 0;
std::vector<Task> graph;
std::vector<Task> criticalPath;

void createGraphModel( const std::vector<Time>&, const std::vector<Connection>& );
void setPredecessors( Task&, const std::vector<Connection>& );
void setSuccessors( Task&, const std::vector<Connection>& );
void countEarlyStartAndFinishRecursively( const int& );
int countEarlyStartFromPredecessors( const std::vector<int>& );
void countLateStartAndFinishRecursively( const int& );
int countLateFinishFromSuccessors( const std::vector<int>& );
void extractCriticalPath();
void designateCriticalPathFromInitialTask();
void designateCriticalPathFromSuccessors( const std::vector<int>& );


void loadDataFile( const std::string& filename )
{
	int n, m;
	Time duration;
	Connection connection;
	std::vector<Time> durations;
	std::vector<Connection> connections;
	std::ifstream file;

	file.open( filename.c_str() );
	if( file.is_open() )
	{
		file >> n >> m;
		for( int i = 0; i < n; ++i )
		{
			file >> duration.optimistic >> duration.possible >> duration.pessimistic;
			durations.push_back( duration );
		}
		for( int i = 0; i < m; ++i )
		{
			file >> connection.from >> connection.to;
			connections.push_back( connection );
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file. The program is stopped." << std::endl;
		std::exit( -1 );
	}

	createGraphModel( durations, connections );
}

void createGraphModel( const std::vector<Time>& durations, const std::vector<Connection>& connections )
{
	Task task;

	for( int i = 0; i < durations.size(); ++i )
	{
		task.id = i + 1;
		task.duration = ( durations[i].optimistic + 4 * durations[i].possible + durations[i].pessimistic ) / 6.0;
		task.variance = std::pow( ( durations[i].pessimistic - durations[i].optimistic ) / 6.0, 2 );
		setPredecessors( task, connections );
		setSuccessors( task, connections );
		graph.push_back( task );

		task.predecessors.clear();
		task.successors.clear();
	}

}

void setPredecessors( Task& task, const std::vector<Connection>& connections )
{
	for( int j = 0; j < connections.size(); ++j )
	{
		if( connections[j].to == task.id &&
			std::find(
				task.predecessors.begin(),
				task.predecessors.end(),
				connections[j].from ) == task.predecessors.end() )
		{
			task.predecessors.push_back( connections[j].from );
		}
	}
}

void setSuccessors( Task& task, const std::vector<Connection>& connections )
{
	for( int j = 0; j < connections.size(); ++j )
	{
		if( connections[j].from == task.id &&
			std::find(
				task.successors.begin(),
				task.successors.end(),
				connections[j].to ) == task.successors.end() )
		{
			task.successors.push_back( connections[j].to );
		}
	}
}

void countEarlyStartAndFinish()
{
	for( int i = 0; i < graph.size(); ++i )
	{
		if( ( graph[i].earlyStart == 0 ) && ( graph[i].earlyFinish == 0 ) ) // jezeli nie bylo jeszcze nic zmieniane
		{
			if( !graph[i].predecessors.empty() )
			{
				for( int j = 0; j < graph[i].predecessors.size(); ++j )
				{
					countEarlyStartAndFinishRecursively( graph[i].predecessors[j] );
				}
				graph[i].earlyStart = countEarlyStartFromPredecessors( graph[i].predecessors );
				graph[i].earlyFinish = graph[i].earlyStart + graph[i].duration;
			}
			else
			{
				graph[i].earlyFinish = graph[i].earlyStart + graph[i].duration;
			}

			if( graph[i].earlyFinish > earliestFinish )
			{
				earliestFinish = graph[i].earlyFinish;
			}
		}
	}
}

void countEarlyStartAndFinishRecursively( const int& taskID )
{
	int idx = taskID - 1; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if( ( graph[idx].earlyStart == 0 ) && ( graph[idx].earlyFinish == 0 ) ) // jezeli nie bylo jeszcze nic zmieniane
	{
		if( !graph[idx].predecessors.empty() )
		{
			for( int i = 0; i < graph[idx].predecessors.size(); ++i )
			{
				countEarlyStartAndFinishRecursively( graph[idx].predecessors[i] );
			}
			graph[idx].earlyStart = countEarlyStartFromPredecessors( graph[idx].predecessors );
			graph[idx].earlyFinish = graph[idx].earlyStart + graph[idx].duration;
		}
		else
		{
			graph[idx].earlyFinish = graph[idx].earlyStart + graph[idx].duration;
		}

		if( graph[idx].earlyFinish > earliestFinish )
		{
			earliestFinish = graph[idx].earlyFinish;
		}
	}
}

int countEarlyStartFromPredecessors( const std::vector<int>& predecessorsIDs )
{
	int predecessorEarlyFinish = 0;
	int earlyStart = earliestStart;

	for( int i = 0; i < predecessorsIDs.size(); ++i )
	{
		predecessorEarlyFinish = graph[predecessorsIDs[i] - 1].earlyFinish;
		if( predecessorEarlyFinish > earlyStart )
		{
			earlyStart = predecessorEarlyFinish;
		}
	}

	return earlyStart;
}

void countLateStartAndFinish()
{
	for( int i = 0; i < graph.size(); ++i )
	{
		if( ( graph[i].lateStart == 0 ) && ( graph[i].lateFinish == 0 ) ) // jezeli nie bylo jeszcze nic zmieniane
		{
			if( !graph[i].successors.empty() )
			{
				for( int j = 0; j < graph[i].successors.size(); ++j )
				{
					countLateStartAndFinishRecursively( graph[i].successors[j] );
				}
				graph[i].lateFinish = countLateFinishFromSuccessors( graph[i].successors );
				graph[i].lateStart = graph[i].lateFinish - graph[i].duration;
			}
			else
			{
				graph[i].lateFinish = latestFinish;
				graph[i].lateStart = graph[i].lateFinish - graph[i].duration;
			}
		}
	}
}

void countLateStartAndFinishRecursively( const int& taskID )
{
	int idx = taskID - 1; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if( ( graph[idx].lateStart == 0 ) && ( graph[idx].lateFinish == 0 ) ) // jezeli nie bylo jeszcze nic zmieniane
	{
		if( !graph[idx].successors.empty() )
		{
			for( int i = 0; i < graph[idx].successors.size(); ++i )
			{
				countLateStartAndFinishRecursively( graph[idx].successors[i] );
			}
			graph[idx].lateFinish = countLateFinishFromSuccessors( graph[idx].successors );
			graph[idx].lateStart = graph[idx].lateFinish - graph[idx].duration;
		}
		else
		{
			graph[idx].lateFinish = latestFinish;
			graph[idx].lateStart = graph[idx].lateFinish - graph[idx].duration;
		}
	}
}

int countLateFinishFromSuccessors( const std::vector<int>& successorsIDs )
{
	int successorLateStart = 0;
	int lateFinish = latestFinish;

	for( int i = 0; i < successorsIDs.size(); ++i )
	{
		successorLateStart = graph[successorsIDs[i] - 1].lateStart;
		if( successorLateStart < lateFinish )
		{
			lateFinish = successorLateStart;
		}
	}

	return lateFinish;
}

void designateTotalFloat()
{
	for( int i = 0; i < graph.size(); ++i )
	{
		graph[i].totalFloat = graph[i].lateStart - graph[i].earlyStart;
		if( graph[i].totalFloat == 0 )
		{
			graph[i].isCritical = true;
		}
	}
}

void showProcessResult( const float& processTime )
{
	double projectVariance = 0.0;
	double expectedProjectDuration = 0.0;

	std::cout << "Process time:\n" << processTime << std::endl;
	std::cout << "\nearlyStart earlyFinish lateStart lateFinish:\n";
	for( int i = 0; i < graph.size(); ++i )
	{
		std::cout << graph[i].earlyStart  << " "
				  << graph[i].earlyFinish << " "
				  << graph[i].lateStart   << " "
				  << graph[i].lateFinish  << std::endl;
	}
	std::cout << "\nCritical path:\n";
	extractCriticalPath();

	for( int i = 0; i < criticalPath.size(); ++i )
	{
		expectedProjectDuration += criticalPath[i].duration;
		projectVariance += criticalPath[i].variance;
	}
	std::cout << "\nExpected project's duration:\n" << expectedProjectDuration << std::endl;
	std::cout << "\nProject's variance:\n" << projectVariance << std::endl;
	std::cout << "\nProject's standard deviation:\n" << std::sqrt( projectVariance ) << std::endl;
	std::cout << "\nProbability completion of the project to 50%:\n" << expectedProjectDuration << std::endl;
	std::cout << "\nProbability completion of the project to 90%:\n" << expectedProjectDuration + sqrt( projectVariance ) * 1.29 << std::endl;
	std::cout << "\nProbability completion of the project to 99%:\n" << expectedProjectDuration + sqrt( projectVariance ) * 2.33 << std::endl;
}

void extractCriticalPath()
{
	designateCriticalPathFromInitialTask();
	std::sort( criticalPath.begin(), criticalPath.end() );
	for( int i = 0; i < criticalPath.size(); ++i )
	{
		std::cout << criticalPath[i].id 		<< " "
				  << criticalPath[i].lateStart  << " "
				  << criticalPath[i].lateFinish << std::endl;
	}
}

void designateCriticalPathFromInitialTask()
{
	for( int i = 0; i < graph.size(); ++i )
	{
		if( graph[i].predecessors.empty() && graph[i].isCritical && !graph[i].visited )
		{
			criticalPath.push_back( graph[i] );
			graph[i].visited = true;
			designateCriticalPathFromSuccessors( graph[i].successors );
			break;
		}
	}
}

void designateCriticalPathFromSuccessors( const std::vector<int>& successors )
{
	int idx = 0;

	for( int i = 0; i < successors.size(); ++i )
	{
		idx = successors[i] - 1;
		if( graph[idx].isCritical && !graph[idx].visited )
		{
			criticalPath.push_back( graph[idx] );
			graph[idx].visited = true;
			if( !graph[idx].successors.empty() )
			{
				designateCriticalPathFromSuccessors( graph[idx].successors );
			}
		}
	}
}


int main( int argc, char* argv[] )
{
	if( argc == 2 )
	{
		loadDataFile( argv[1] );

		const clock_t begin = std::clock();
		{
			countEarlyStartAndFinish();
			latestFinish = earliestFinish;
			countLateStartAndFinish();
			designateTotalFloat();
		}
		const float end = static_cast<float>( std::clock() - begin ) / CLOCKS_PER_SEC * 1000;

		showProcessResult( end );

		return 0;
	}
	else
	{
		std::cerr << "Bad number of arguments for main function" << std::endl;
		return -1;
	}
}
