$.getJSON('http://localhost:3000/modules', function(data) {
    var app = angular.module('MyApp', ["ngRoute"]);
    app.controller('MyController', function ($scope) {
        $scope.Customers = data;
        $scope.IsVisible = true;
        var statusvalue = $('[ng-controller="MyController"]').scope().Customers;
        var length = Object.keys(statusvalue).length;
        console.log(length);
        for (var i=0;i<=length;i++) {
            var statuses = statusvalue[i].status;
            console.log(statuses);
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
    function openNav() {
        document.getElementById("mySidenav").style.width = "250px";
    }
    function closeNav() {
        document.getElementById("mySidenav").style.width = "0";
    }