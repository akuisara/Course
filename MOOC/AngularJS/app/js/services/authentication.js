myApp.factory("Authentication", function($firebase, $firebaseSimpleLogin,FIREBASE_URL, $location, $rootScope){
	var loginRef = new Firebase(FIREBASE_URL);
	var simpleLogin = $firebaseSimpleLogin(loginRef);

	var myObject = {
		login: function(user){
			var userRef = new Firebase(FIREBASE_URL + "/users/" + user.uid);
			var userObj = $firebase(userRef).$asObject();

			userObj.$loaded().then(function(){
				$rootScope.createUser = userObj;
			})

			return simpleLogin.$login("password",{
				email: user.email,
				password: user.password
			});
		},

		register: function(user){
			return simpleLogin.$createUser(user.email, user.password)
			.then(function(registerUser){
				var userRef = new Firebase(FIREBASE_URL + "users");
				var fireBaseUsers = $firebase(userRef);

				var userInfo = {
					data: Firebase.ServerValue.TIMESTAMP,
					registerUser: registerUser.uid,
					username: user.username,
					email: user.email
				}

				fireBaseUsers.$set(registerUser.uid, userInfo);
			});
		},

		logout: function(){
			return simpleLogin.$logout();
		},

		signedIn: function(){
			return simpleLogin.user != null;
		}
	};

	$rootScope.signedIn = function(){
		return myObject.signedIn();
	}
	
	return myObject;
});