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
            if(item == "active"){
            return {
                'color': '#52daaa'
            }
            }
            if(item == "inactive"){
                return {
                    'color': 'red'
                }
            }
        }
        var i = 0;
        $scope.calculateHeight = function(item){
            var backgroundcolor;
            var total = $scope.Customers[i].length;
            console.log(item);
                var a= document.getElementsByClassName('wave');
                var b=document.getElementsByClassName('wave1');
                var c=document.getElementsByClassName('wave2');
                a[i].style.top = total-item;
                b[i].style.top = total-item;
                c[i].style.top = total-item;
                i++;
        }      
    });
    });



