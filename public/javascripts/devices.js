$.getJSON('http://localhost:8000/modules', function(data) {
    var app = angular.module('MyApp', ["ngRoute"]);
    app.controller('MyController', function ($scope) {
        $scope.Customers = data;
        $scope.IsVisible = true;
        var statusvalue = $('[ng-controller="MyController"]').scope().Customers;
        var length = Object.keys(statusvalue).length;
        for (var i=0;i<=length;i++) {
            var statuses = statusvalue[i].status;
            i++;
        }
        $scope.calculateStyle = function(item){
            var color;
            // Some logic to define color
            if(item == "Active"){
            return {
                'color': '#52daaa'
            }
            }
            if(item == "Inactive"){
                return {
                    'color': 'red'
                }
            }
        }
    });
    });
    function closeNav() {
        var width = document.getElementById("mySidenav").offsetWidth;
        if(width!=0){
            $(".sidenav").hide();
        }
        if(width===0){
            $(".sidenav").show();
        }
    }