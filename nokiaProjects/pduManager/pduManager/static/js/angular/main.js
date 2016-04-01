var pduApp = angular.module('pduApp', []);
pduApp.config(function($interpolateProvider) {
  $interpolateProvider.startSymbol('{[{');
  $interpolateProvider.endSymbol('}]}');
});

pduApp.controller('mainController', function ($scope) {
  $scope.groups = [
    {
      id: 1,
      name: "group1",
      pdus: []
    },
    {
      id: 2,
      name: "group2",
      pdus: []
      },
      {
        id: 3,
        name: "group3",
        pdus: []
        }
  ]

  $scope.arrayPdu = [
    {
      id: "1",
      name: "PDU 1",
      ip: "192.168.1.1",
      slots: "2",
      descr: "fajne PDU",
      dispMoreInfo: false,
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
      slots: "3",
      descr: "fajne PDU",
      dispMoreInfo: false,
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
  ];
  $scope.selectLabelAdiingGroup = function(pdu){
    $scope.selectedLabel = pdu.id;
  }
  $scope.tooglePduInformations = function(pdu){
    if(pdu.dispMoreInfo == false){
      pdu.dispMoreInfo  = true;
    }else{
      pdu.dispMoreInfo  = false;
    }
  }

  $scope.createEmptyGroup = function(){
    $scope.newGroup = {
      name: "",
      properties: angular.copy($scope.arrayPdu)
    }
    $scope.selectedLabel = $scope.arrayPdu[0].id;

  }
  $scope.createNewGroup = function(){
    console.log($scope.newGroup);
    var element = {
      id: $scope.maxId + 1,
      name: $scope.newGroup.name,
      pdus: $scope.newGroup.properties
    }
    $scope.groups.push(element);
  }
  $scope.maxId = function(array){
    var max = -1;
    for(var i = 0; i < array.size; i++){
      if(array[i].id > max){
        max = array[i].id;
      }
    }
    return max;
  }
  $scope.removeGroup = function(id){
    for(var i = $scope.groups.length - 1; i >= 0; i--) {
      if($scope.groups[i].id === id) {
        $scope.groups.splice(i, 1);
        break;
      }
    }   
  }
});
