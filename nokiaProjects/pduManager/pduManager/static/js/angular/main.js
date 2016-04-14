var pduApp = angular.module('pduApp', []);
pduApp.config(function($interpolateProvider) {
  $interpolateProvider.startSymbol('{[{');
  $interpolateProvider.endSymbol('}]}');
});

pduApp.controller('mainController', function ($scope) {

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

  $scope.groups = [
    {
      id: 0,
      name: "all",
      allDevices: angular.copy($scope.arrayPdu)
    }
  ]

  $scope.init = function(){
    $scope.selectGroup(0);
  }
  $scope.selectGroup = function(id){
    if(id == 0){
      $scope.selectedGroup = $scope.groups[0];
      for(var i = 0 ; i < $scope.selectedGroup.allDevices.length; ++i){
        $scope.selectedGroup.allDevices[i].selected = true;
        for(var j = 0 ; j < $scope.selectedGroup.allDevices[i].arraySlots.length; ++j){
          $scope.selectedGroup.allDevices[i].arraySlots[j].selected = true;
        }
      }
    }
    else{
      for(var i = 0; i < $scope.groups.length; i++){
        if($scope.groups[i].id == id){
          $scope.selectedGroup = $scope.groups[i];
          break;
        }
      }
    }
  }
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
      id: $scope.maxId() + 1,
      allDevices: angular.copy($scope.arrayPdu),
      name: ""
    }
    $scope.selectedLabel = $scope.arrayPdu[0].id;
  }
  $scope.addPduToGroup = function(pdu, slot){
    if(slot.selected == true){
      pdu.selected = true;
    }else{
      pdu.selected = false;
    }
  }

  $scope.confirmGroup = function(){
    $scope.groups.push($scope.newGroup);
  }

  $scope.maxId = function(){
    var max = -1;
    for(var i = 0; i < $scope.groups.length; i++){
      if($scope.groups[i].id > max){
        max = $scope.groups[i].id;
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
