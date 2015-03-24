myApp.factory("Authentication", function($firebase, $firebaseSimpleLogin,FIREBASE_URL, $location){
	var loginRef = new Firebase(FIREBASE_URL);
	var simpleLogin = $firebaseSimpleLogin(loginRef);

	var myObject = {
		login: function(user){
			return simpleLogin.$login("password",{
				email: user.email,
				password: user.password
			});
		},

		register: function(user){
			return simpleLogin.$createUser(user.email, user.password);
		},

		logout: function(){
			return simpleLogin.$logout();
		}
	};
	
	return myObject;
});