var pduApp = angular.module('pduApp', ["checklist-model"]);
pduApp.config(function($interpolateProvider) {
  $interpolateProvider.startSymbol('{[{');
  $interpolateProvider.endSymbol('}]}');
});
pduApp.config(function($httpProvider){
    $httpProvider.defaults.xsrfCookieName = 'csrftoken'
    $httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken'
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

pduApp.controller('mainController',['$scope', '$http', 'repository', function ($scope, $http, repository){
  $scope.descr = {
    editedPduDescrText: "",
    editedSlotDescrText: ""
  }
  $scope.arrayPdu = {};
  $scope.groups = [
    {
      id: 0,
      name: "all",
      idPdus: [],
      idSlots: []
    }
  ]
  $scope.templates = ['display_devices', 'display_groups'];

  $scope.loadAllDevices = function(){
    $http({
      url: "/api/pdus/",
      method: "GET",
    }).success(function(data, status, headers, config){
      for(var i = 0; i < data.length; ++i){
        var element = {
          name: data[i].name,
          ip: data[i].ip,
          descr: data[i].description,
          arraySlots: {}
        }
        $scope.arrayPdu[data[i].id] = element;
        $scope.groups[0].idPdus.push(data[i].id);
      }
    }).error(function(data, status, headers, config){
      console.log("error");
    })

    $http({
      url: "/api/outlets/",
      method: "GET",
    }).success(function(data, status, headers, config){
      for(var i = 0; i < data.length; ++i){
        var element = {
          nr: i + 1,
          state: "unknown",
          descr: data[i].description,
          pduId: data[i].pdu.id
        }
        $scope.arrayPdu[data[i].pdu.id].arraySlots[data[i].id] = element;
        $scope.groups[0].idSlots.push(data[i].id);
        $scope.selectGroup(0);
        $scope.filteredPdus = $scope.selectedGroup.idPdus;
        $scope.pagination = {
          currentPage: 1,
          entryLimit: 1,
          noOfPages: 0,
          limitPages: 5
        };
        $scope.pagination.noOfPages = Math.ceil($scope.filteredPdus.length/$scope.pagination.entryLimit);
      }
    }).error(function(data, status, headers, config){
      console.log("error");
    })
  }

  $scope.init = function(){
    $scope.loadAllDevices();
    $scope.contentOfTab = $scope.templates[0];
  }
  $scope.selectGroup = function(id){
    $scope.contentOfTab = $scope.templates[0];
    if(id == 0){
      $scope.selectedGroup = $scope.groups[0];
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
  $scope.selectLabelAdiingGroup = function(pduId){
    $scope.selectedLabel = pduId;
  }
  $scope.tooglePduInformations = function(pdu){
    if(pdu.dispMoreInfo != true){
      pdu.dispMoreInfo  = true;
    }else{
      pdu.dispMoreInfo  = false;
    }
  }

  $scope.createEmptyGroup = function(){
    $scope.modeGroup = "add";
    $scope.newGroup = {
      id: $scope.maxId() + 1,
      name: "",
      idPdus: [],
      idSlots: []
    }
    $scope.selectedLabel = 1;
  }

  $scope.confirmGroup = function(){
    if($scope.modeGroup == 'add'){
      for (var pduId in $scope.arrayPdu) {
        for(var slotId in $scope.arrayPdu[pduId].arraySlots){
          if($scope.newGroup.idSlots.indexOf(slotId) != -1){
            $scope.newGroup.idPdus.push(pduId);
            break;
          }
        }
      }
      $scope.groups.push($scope.newGroup);
      for(var i = 0; i < $scope.groups.length; ++i){
        if($scope.groups[i].id == $scope.newGroup.id){
          $scope.selectedGroup = $scope.groups[i];
          break;
        }
      }
      $('#menuGroups').addClass("active");
      $('#secondLevelMenu').addClass('in');
      $('.nav.nav-second-level.collapse').css('height', 'auto');
    }
    else if($scope.modeGroup == 'edit'){
      $scope.newGroup.idPdus = [];
      for (var pduId in $scope.arrayPdu) {
        for(var slotId in $scope.arrayPdu[pduId].arraySlots){
          if($scope.newGroup.idSlots.indexOf(slotId) != -1){
            $scope.newGroup.idPdus.push(pduId);
            break;
          }
        }
      }
      for(var i = 0; i < $scope.groups.length; i++){
        if($scope.groups[i].id == $scope.newGroup.id){
          $scope.groups[i] = angular.copy($scope.newGroup);
          break;
        }
      }
      if($scope.groups[i].id == $scope.selectedGroup.id)
        $scope.selectedGroup = $scope.groups[i];
    }
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
    $scope.selectedGroup = $scope.groups[0];
  }

  $scope.getNumberPages = function() {
    return new Array($scope.pagination.noOfPages);
  }
  $scope.changePage = function(page){
    if(page <= $scope.pagination.noOfPages && page > 0){
      $scope.pagination.currentPage = page;
    }
  }
  $scope.$watch('selectedGroup', function listener(nVal, oVal){
    if (nVal != oVal){
      $scope.filteredPdus = $scope.selectedGroup.idPdus;
      $scope.pagination.noOfPages = Math.ceil($scope.filteredPdus.length/$scope.pagination.entryLimit);
      $scope.pagination.currentPage = 1;
    }
  })
  $scope.$watch('pagination.entryLimit', function listener(nVal, oVal){
    if (nVal != oVal){
      if($scope.pagination.entryLimit < 1){
        $scope.pagination.entryLimit = 1;
      }
      $scope.pagination.noOfPages = Math.ceil($scope.filteredPdus.length/$scope.pagination.entryLimit);
      //$scope.currentPage = 1;
    }
  })
  $scope.editPduDescr = function(pdu, pduId){
    $scope.descr.editedPduDescrText = angular.copy(pdu.descr);
    $scope.editedPdu = pduId;
  }
  $scope.confirmDescr = function(pdu){
    $scope.editedPdu = undefined;
    pdu.descr = $scope.descr.editedPduDescrText
  }
  $scope.rejectDescr = function(){
    $scope.editedPdu = undefined;
  }
  $scope.editSlotDescr = function(slot, pduId, slotId){
    $scope.descr.editedSlotDescrText = angular.copy(slot.descr);
    $scope.editedslot = slotId;
    $scope.editedSlotFromPdu = pduId;
  }
  $scope.rejectSlotDescr = function(){
    $scope.editedslot = undefined;
    $scope.editedSlotFromPdu = undefined;
  }
  $scope.confirmSlot = function(slot){
    $scope.editedslot = undefined;
    $scope.editedSlotFromPdu = undefined;
    slot.descr = $scope.descr.editedSlotDescrText;
  }
  $scope.editGroup = function(group){
    $scope.selectedLabel = 1;
    $scope.modeGroup = "edit";
    $scope.newGroup = angular.copy(group);
  }
  $scope.switchOnSlot = function(pdu, slot){
    $scope.busy = true;
    $http({
      url: "/pdu_communicator/switch_outlet_on",
      method: "GET",
      params: {
        pdu_ip: pdu.ip,
        outlet_nr: slot.nr
      }
    }).success(function(data, status, headers, config){
      if(data.result == true){
        $scope.busy = false;
        slot.state = 'active';
        $.notify("Outlet has been activated properly", {position: "top center", className: "success"});
      }
      else
      {
        $scope.busy = false;
        slot.state = 'active';
        $.notify("Outlet is currently active", {position: "top center", className: "warn"});
      }
    }).error(function(data, status, headers, config){
      $scope.busy = false;
      $.notify("activation failed", {position: "top center", className: "error"});
      slot.state = 'unknown';
    })
  }

  $scope.switchOffSlot = function(pdu, slot){
    $scope.busy = true;
    $http({
      url: "/pdu_communicator/switch_outlet_off",
      method: "GET",
      params: {
        pdu_ip: pdu.ip,
        outlet_nr: slot.nr
      }
    }).success(function(data, status, headers, config){
      if(data.result == true){
        $scope.busy = false;
        slot.state = 'disable';
        $.notify("Outlet has been disactivated properly", {position: "top center", className: "success"});
      }
      else
      {
        $scope.busy = false;
        slot.state = 'disable';
        $.notify("Outlet is currently disactive", {position: "top center", className: "warn"});
      }
    }).error(function(data, status, headers, config){
      $scope.busy = false;
      $.notify("disactivation failed", {position: "top center", className: "error"});
      slot.state = 'unknown';
    })
  }

  $scope.resetSlot = function(pdu, slot){
    $scope.busy = true;
    $http({
      url: "/pdu_communicator/reset_outlet",
      method: "GET",
      params: {
        pdu_ip: pdu.ip,
        outlet_nr: slot.nr
      }
    }).success(function(data, status, headers, config){
      if(data.result == true){
        $scope.busy = false;
        slot.state = 'active';
        $.notify("Outlet has been reseted properly", {position: "top center", className: "success"});
      }
      else
      {
        $scope.busy = false;
        slot.state = 'disable';
        $.notify("Outlet is currently disactive", {position: "top center", className: "warn"});
      }
    }).error(function(data, status, headers, config){
      $scope.busy = false;
      $.notify("reset failed", {position: "top center", className: "error"});
      slot.state = 'unknown';
    })
  }
  $scope.displayAllGroups = function(){
    $scope.contentOfTab = $scope.templates[1];

    $http({
      url: "/api/groups/",
      method: "GET",
    }).success(function(data, status, headers, config){
      $scope.allGroups = data;
    }).error(function(data, status, headers, config){
      console.log("error");
    })
  }

}]);
