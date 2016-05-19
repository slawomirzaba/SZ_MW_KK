angular.module('pduApp').factory('repository', [function(){
	return{
		arrayPdu :
		{
			1 : {
		      name: "PDU 1",
		      ip: "192.168.0.60",
		      descr: "fajne PDU",
		      arraySlots: {
		        1: {
				  nr: 1,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        2: {
				  nr: 2,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
				3: {
				  nr: 3,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        4: {
				  nr: 4,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
				5: {
				  nr: 5,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        6: {
				  nr: 6,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
				7: {
				  nr: 7,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        8: {
				  nr: 8,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		      }
		    },
		    2 : {
		      name: "PDU 2",
		      ip: "192.168.0.60",
		      descr: "fajne PDU",
		      arraySlots: {
		        9: {
				  nr: 1,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        10: {
				  nr: 2,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
				11: {
				  nr: 3,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        },
		        12: {
				  nr: 4,
		          state: "unknown",
		          descr: "fajny socket",
		          pduId: 1
		        }
		      }
		    }
		}
	};
}]);
