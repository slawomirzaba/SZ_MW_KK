var pduApp = angular.module('pduApp', []);
pduApp.config(function($interpolateProvider) {
  $interpolateProvider.startSymbol('{[{');
  $interpolateProvider.endSymbol('}]}');
});

pduApp.controller('mainController', function ($scope) {
  $scope.groups = [
    {
      id: 0,
      name: "all",
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
  
  $scope.selectedGroup = $scope.groups[0];
  $scope.selectGroup = function(id){
    for(var i = 0; i < $scope.groups.length; i++){
      if($scope.groups[i].id == id){
        $scope.selectedGroup = $scope.groups[i];
        break;
      }
    }
  }
  $scope.isPduinGroup = function(pduId){
    if($scope.selectedGroup.name == "all" && $scope.selectedGroup.id ==  0){
      return true;
    }
    for(var i = 0; i < $scope.selectedGroup.pdus.length; i++){
      if($scope.selectedGroup.pdus[i].pduId == pduId)
        return true;
    }
    return false;
  }
  $scope.isSlotinGroup = function(pduId, slotId){
    if($scope.selectedGroup.name == "all" && $scope.selectedGroup.id ==  0){
      return true;
    }
    for(var i = 0; i < $scope.selectedGroup.pdus.length; i++){
      if($scope.selectedGroup.pdus[i].pduId == pduId)
      {
        index = i;
        break;
      }
    }
    for(var j = 0; j < $scope.selectedGroup.pdus[index].slots.length; ++j){
      if($scope.selectedGroup.pdus[index].slots[j] == slotId){
        return true;
      }
    }
    return false;
  }

  $scope.isInArrayNewGroup = function(pduId){
    for(var i = 0; i < $scope.newGroup.properties.length; ++i){
      if($scope.newGroup.properties[i].pduId == pduId){
        return i;
      }
    }
    return -1;
  }
  $scope.selectPduToGroup = function(pdu, slot){
    if(slot.selected == true)
    {
      index = $scope.isInArrayNewGroup(pdu.id);
      if(index != -1)
      {
        $scope.newGroup.properties[index].slots.push(slot.id);
      }
      else
      {
          var element = {
          pduId: pdu.id,
          slots: [slot.id]
        }
        $scope.newGroup.properties.push(element);
      }
    }
    else
    {
      for( var i = 0; i < $scope.newGroup.properties.length; ++i)
      {
        for ( var j = 0; j < $scope.newGroup.properties[i].slots.length; ++j)
        {
          if($scope.newGroup.properties[i].pduId == pdu.id && $scope.newGroup.properties[i].slots[j] == slot.id)
          {
            $scope.newGroup.properties[i].slots.splice(j, 1);
            if($scope.newGroup.properties[i].slots.length == 0){
              $scope.newGroup.properties.splice(i, 1);
            }
            break;
          }
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
      allDevices: angular.copy($scope.arrayPdu),
      name: "",
      properties: []
    }
    $scope.selectedLabel = $scope.arrayPdu[0].id;

  }
  $scope.createNewGroup = function(){
    console.log($scope.newGroup);
    var element = {
      id: $scope.maxId() + 1,
      name: angular.copy($scope.newGroup.name),
      pdus: angular.copy($scope.newGroup.properties)
    }
    $scope.groups.push(element);
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
