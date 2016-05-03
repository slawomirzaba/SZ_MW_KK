angular.module('pduApp').factory('repository', [function(){
	return{
		arrayPdu :
		[
			{
		      id: "1",
		      name: "PDU 1",
		      ip: "192.168.1.1",
		      descr: "fajne PDU",
		      arraySlots: [
		        {
		          id: "1",
		          state: "active",
		          descr: "fajny socket"
		        },
		        {
		          id: "2",
		          state: "disable",
		          descr: "fajny socket"
		        },
		      ]
		    },
		    {
		      id: "2",
		      name: "PDU 2",
		      ip: "192.168.1.21",
		      descr: "fajne PDU",
		      arraySlots: [
		        {
		          id: "1",
		          state: "active",
		          descr: "fajny socket"
		        },
		        {
		          id: "2",
		          state: "disable",
		          descr: "fajny socket"
		        },
		        {
		          id: "3",
		          state: "active",
		          descr: "fajny socket"
		        }
		      ]
		    },
		    {
		      id: "3",
		      name: "PDU 3",
		      ip: "192.168.1.23",
		      descr: "fajne PDU",
		      arraySlots: [
		        {
		          id: "1",
		          state: "active",
		          descr: "fajny socket"
		        },
		        {
		          id: "2",
		          state: "disable",
		          descr: "fajny socket"
		        },
		        {
		          id: "3",
		          state: "active",
		          descr: "fajny socket"
		        }
		      ]
		    }
		]
	};
}]);