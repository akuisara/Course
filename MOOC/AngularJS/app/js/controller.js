var exampleController = angular.module("exampleController",["firebase"]);

exampleController.controller("LoginController", ["$scope","$firebaseSimpleLogin","$location", "Authentication", function MyController($scope, $firebaseSimpleLogin, $location, Authentication){

	$scope.login = function(){
		Authentication.login($scope.user)
		.then(function(user){
			$location.path("/dashboard");
		}, function(error){
			$scope.message = error.toString();
		});
	};

	$scope.register = function(){
		Authentication.register($scope.user)
		.then(function(user){
			Authentication.login($scope.user);
			$location.path("/dashboard");
		}, function(error){
			$scope.message = error.toString();
		});
	};
}]);

exampleController.controller("StatusController", ["$scope", "$firebaseSimpleLogin", "$rootScope", "$location", "Authentication", "$firebase", "FIREBASE_URL", function MyController($scope, $firebaseSimpleLogin, $rootScope, $location, Authentication, $firebase, FIREBASE_URL){

	$scope.logout = function() {
		Authentication.logout();
		$location.path("/login");
	};

	$rootScope.$on('$firebaseSimpleLogin:login', function(e, authUser) {
		var ref = new Firebase(FIREBASE_URL + "/users/" + authUser.uid);
		var user = $firebase(ref).$asObject();

		user.$loaded().then(function(){
			$rootScope.currentUser = user;
		})
	});

	$rootScope.$on('$firebaseSimpleLogin:logout', function(e, authUser) {
		$rootScope.currentUser = null;
	});
}]);
	
exampleController.controller("DashboardController", ["$scope", "$firebase", "$firebaseSimpleLogin", "$rootScope", "FIREBASE_URL", function MyController($scope, $firebase, $rootScope, FIREBASE_URL, $firebaseSimpleLogin){

	var ref = new Firebase(FIREBASE_URL);
	var simpleLogin = $firebaseSimpleLogin(ref);

	$simpleLogin.$getCurrentUser().then(function (authUser){
		if (authUser !== null){
			var firebaseRef = new Firebase(FIREBASE_URL + "/user/" + authUser.uid + "/dashboard");
			var firebaseContent = $firebase(firebaseRef);
			var contentObj = $firebase(firebaseRef).$asObject();
			var contentArray = $firebase(firebaseRef).$asArray();

			contentObj.$loaded().then(function (data) {
				$scope.userDashboard = contentObj;
			});

			contentArray.$loaded().then(function (data) {
				$rootScope.contentNum = contentArray.length;
			});

			contentArray.$watch(function (event) {
				$rootScope.contentNum = contentArray.length;
			});

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
		}
	});
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