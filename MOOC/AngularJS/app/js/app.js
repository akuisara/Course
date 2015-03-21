var myApp = angular.module("myApp", [
	"ngRoute",
	"firebase",
	"exampleController"
]).constant("FIREBASE_URL", "https://flickering-fire-7979.firebaseio.com/dashboard");

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
		redirectTo:"/login"
	});
}]);