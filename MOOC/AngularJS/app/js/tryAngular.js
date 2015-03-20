var exampleController = angular.module("exampleController",["firebase"]);

exampleController.controller("LoginController", ["$scope","$firebaseSimpleLogin","$location", function MyController($scope, $firebaseSimpleLogin, $location){
	var loginRef = new Firebase("https://flickering-fire-7979.firebaseio.com/dashboard");
	var simpleLogin = $firebaseSimpleLogin(loginRef);

	$scope.login = function(){
		simpleLogin.$login("password",{
			email: $scope.user.email,
			password: $scope.user.password
		}).then(function(user){
			$location.path("/dashboard");
		}, function(error){
			$scope.message = error.toString();
		});
	}

	$scope.register = function(){
		$location.path("/dashboard");
	};
}]);
	
exampleController.controller("DashboardController", ["$scope", "$firebase", function MyController($scope, $firebase){

	var firebaseRef = new Firebase("https://flickering-fire-7979.firebaseio.com/dashboard");
	var firebaseContent = $firebase(firebaseRef);

	$scope.firebaseContent = firebaseContent.$asObject();

	$scope.addContent = function(){
		firebaseContent.$push({
			name: $scope.contentName,
			description: $scope.contentDescription,
			date: Firebase.ServerValue.TIMESTAMP
		}).then(function(){
			$scope.contentName = "";
			$scope.contentDescription = "";
		});
	};

	$scope.deleteContent = function(key){
		firebaseContent.$remove(key);
	};
}]);

exampleController.controller("ListController", ["$scope", "$http", function MyController($scope, $http){
	$http.get("js/example.json").success(function(data){
		$scope.choices = data;
	});
}]);

exampleController.controller("DetailsController", ["$scope", "$http", "$routeParams", function MyController($scope, $http, $routeParams){
	$http.get("js/example.json").success(function(data){
		$scope.choices = data;
		$scope.whichChoice = $routeParams.itemInstruction;

		if ($routeParams.itemInstruction > 0) {
			$scope.prevItem = Number($routeParams.itemInstruction) - 1;
		} else {
			$scope.prevItem = $scope.choices.length - 1;
		}

		if ($routeParams.itemInstruction < ($scope.choices.length - 1)) {
			$scope.nextItem = Number($routeParams.itemInstruction) + 1;
		} else {
			$scope.nextItem = 0;
		}
	});
}]);