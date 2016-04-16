var pduApp = angular.module('pduApp', []);
pduApp.config(function($interpolateProvider) {
  $interpolateProvider.startSymbol('{[{');
  $interpolateProvider.endSymbol('}]}');
});

pduApp.filter('startFrom', function() {
    return function(input, start) {
        if(input) {
            start = +start; //parse to int
            return input.slice(start);
        }
        return [];
    }
});

pduApp.controller('mainController', function ($scope) {

  $scope.arrayPdu = [
    {
      id: "1",
      name: "PDU 1",
      ip: "192.168.1.1",
      slots: "2",
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
      slots: "3",
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
      slots: "3",
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
    $scope.filteredPdus = $scope.groups[0].allDevices;
    $scope.currentPage = 1; //current page
    $scope.entryLimit = 1; //max rows for data table
    $scope.noOfPages = Math.ceil($scope.filteredPdus.length/$scope.entryLimit);
    $scope.limitPages = 5;
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
    if(pdu.dispMoreInfo != true){
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
  $scope.test = function(){
    console.log($scope.groups[0].allDevices.map(function(e) { return e.id; }).indexOf('1'));
  }

    /* init pagination with $scope.list */
  $scope.getNumberPages = function() {
    return new Array($scope.noOfPages);   
  }
  $scope.changePage = function(page){
    if(page <= $scope.noOfPages && page > 0){
      $scope.currentPage = page;
    }
  }
  $scope.$watchCollection('filteredPdus', function listener(nVal, oVal){
    if (nVal != oVal){
      $scope.noOfPages = Math.ceil($scope.filteredPdus.length/$scope.entryLimit);
      $scope.currentPage = 1;
    }
  })
  $scope.editPduDescr = function(id){
    $scope.editedPdu = id;
  }
  $scope.confirmDescr = function(pdu){
    $scope.editedPdu = undefined;
    angular.forEach($scope.groups, function(g, i){
      angular.forEach(g.allDevices, function(d, j){
        if(d.id == pdu.id){
          d.descr = pdu.descr;
        }
      });
    });
  }
  $scope.rejectDescr = function(id){
    $scope.editedPdu = undefined;
  }
  $scope.editSlotDescr = function(slotId, pduId){
    $scope.editedslot = slotId;
    $scope.editedSlotFromPdu = pduId;
  }
  $scope.rejectSlotDescr = function(id){
    $scope.editedslot = undefined;
    $scope.editedSlotFromPdu = undefined;
  }
});
