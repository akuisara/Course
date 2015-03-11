var gulp = require("gulp"),
	util = require("gulp-util"),
	webserver = require("gulp-webserver");

gulp.task("js", function(){
	gulp.src(["js/*.js","js/lib/Angular/*.js"]);
});

gulp.task("html", function(){
	gulp.src("index.html");
});

gulp.task("watch", function(){
	gulp.watch("js/**/*.js",["js"]);
	gulp.watch(["index.html","partials/*.html"],["html"]);
});

gulp.task("webserver", function(){
	gulp.src("app")
	.pipe(webserver({
		livereload:true,
		open:true
	}));
});

gulp.task("default", ["watch", "html", "js", "webserver"]);