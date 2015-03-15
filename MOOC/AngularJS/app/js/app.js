var myApp = angular.module("myApp", [
	"ngRoute",
	"exampleController"
]);

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
		templateUrl: "partials/dashboard.html"
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
		redirectTo:"/login"
	});
}]);