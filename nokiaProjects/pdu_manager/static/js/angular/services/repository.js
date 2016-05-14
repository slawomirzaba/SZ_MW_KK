angular.module('pduApp').factory('repository', [function(){
	return{
		arrayPdu :
		[
			{
		      id: "1",
		      name: "PDU 1",
		      ip: "192.168.0.60",
		      descr: "fajne PDU",
		      arraySlots: [
		        {
		          id: "1",
				  nr: 1,
		          state: "unknown",
		          descr: "fajny socket"
		        },
		        {
		          id: "2",
				  nr: 2,
		          state: "unknown",
		          descr: "fajny socket"
		        },
						{
		          id: "1",
				  nr: 3,
		          state: "unknown",
		          descr: "fajny socket"
		        },
		        {
		          id: "2",
				  nr: 4,
		          state: "unknown",
		          descr: "fajny socket"
		        },
						{
		          id: "5",
				  nr: 5,
		          state: "unknown",
		          descr: "fajny socket"
		        },
		        {
		          id: "6",
				  nr: 6,
		          state: "unknown",
		          descr: "fajny socket"
		        },
				{
		          id: "7",
				  nr: 7,
		          state: "unknown",
		          descr: "fajny socket"
		        },
		        {
		          id: "8",
				  nr: 8,
		          state: "unknown",
		          descr: "fajny socket"
		        },
		      ]
		    }
		]
	};
}]);
