var tryAngular = angular.module("tryAngular",[]);

tryAngular.controller("MyController", ["$scope", "$http", function MyController($scope, $http){
	$http.get("js/example.json").success(function(data){
		$scope.option = data;
	});
}]);