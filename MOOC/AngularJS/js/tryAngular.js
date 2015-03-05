var exampleController = angular.module("exampleController",[]);

exampleController.controller("ListController", ["$scope", "$http", function MyController($scope, $http){
	$http.get("js/example.json").success(function(data){
		$scope.choices = data;
	});
}]);

exampleController.controller("DetailsController", ["$scope", "$http", "$routeParams", function MyController($scope, $http, $routeParams){
	$http.get("js/example.json").success(function(data){
		$scope.choices = data;
		$scope.whichChoice = $routeParams.itemInstruction;
	});
}]);