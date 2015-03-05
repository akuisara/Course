var myApp = angular.module("myApp", [
	"ngRoute",
	"exampleController"
]);

myApp.config(["$routeProvider", function($routeProvider){
	$routeProvider.
	when("/list", {
		templateUrl: "partials/list.html",
		controller: "ListController"
	}).
	when("/details/:itemInstruction", {
		templateUrl: "partials/details.html",
		controller: "DetailsController"
	}).
	otherwise({
		redirectTo:"/list"
	});
}]);