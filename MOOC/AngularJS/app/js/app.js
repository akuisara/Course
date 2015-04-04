var myApp = angular.module("myApp", [
	"ngRoute",
	"firebase",
	"exampleController"
]).constant("FIREBASE_URL", "https://flickering-fire-7979.firebaseio.com/");

myApp.run(['$rootScope', '$location', function($rootScope, $location) {
  $rootScope.$on('$routeChangeError',
  function(event, next, previous, error) {
    if(error === 'AUTH_REQUIRED') {
      $rootScope.message='Sorry, please log in first';
      $location.path('/login');
    }
  });
}]);

myApp.config(["$routeProvider", function($routeProvider){
	$routeProvider.
	when("/login", {
		templateUrl: "partials/login.html",
		controller: "LoginController"
	}).
	when("/register", {
		templateUrl: "partials/register.html",
		controller: "LoginController"
	}).
	when("/dashboard", {
		templateUrl: "partials/dashboard.html",
		controller: "DashboardController"
	}).
	when("/list", {
		templateUrl: "partials/list.html",
		controller: "ListController"
	}).
	when("/details/:itemInstruction", {
		templateUrl: "partials/details.html",
		controller: "DetailsController"
	}).
	otherwise({
		redirectTo:"/dashboard"
	});
}]);