$( document ).ready(function() {
    var players = [];

    var data = $.ajax({
        url: 'data/sportsData.xml',
        dataType: 'xml',
        async: false,
        success: function(data){
            players = [];
            $(data).select("baseball").find("player").each(function() {
                temp = {};
                temp["Name"] = $(this).find("name").text();
                temp["Height"] = $(this).find("height").text();
                temp["Weight"] = $(this).find("weight").text();
                temp["Average"] = $(this).find("average").text();
                temp["OBP"] = $(this).find("OBP").text();
                temp["Homeruns"] = $(this).find("home_runs").text();
                temp["Team"] = $(this).prev().text();
                players.push(temp);
            });
            getGraph();
        },
        error: function(data){
            console.log('Failed to load the input file.');
        }
    });

    $("#apply").click(function() {
        d3.select("svg").remove();
        getGraph();
    })

    function getGraph(){
        options = {
            "optionX": $("#x").val(), 
            "optionY": $("#y").val(), 
            "optionR":$("#circleRadius").val(), 
            "optionC": $("#circleColor").val()
        };

        xDomain = d3.extent(players, function(d) { 
            return d[options.optionX]; 
        });

        yDomain = d3.extent(players, function(d) { 
            return d[options.optionY]; 
        });

        rDomain = d3.extent(players, function(d) { 
            return d[options.optionR]; 
        });

        // set the stage
        var margin = {t:30, r:20, b:20, l:40 },
            w = 600 - margin.l - margin.r,
            h = 350 - margin.t - margin.b,
            x = d3.scale.linear().range([0, w]).domain([xDomain[0] * 0.95, xDomain[1] * 1.05]).nice(),
            y = d3.scale.linear().range([h - 60, 0]).domain([yDomain[0] * 0.95, yDomain[1] * 1.05]).nice(),
            r = d3.scale.linear().range([5, 20]).domain(rDomain).nice(),
            //colors that will reflect geographical regions
            color = d3.scale.category10();

        var svg = d3.select("#viz").append("svg")
            .attr("width", w + margin.l + margin.r)
            .attr("height", h + margin.t + margin.b)
            .classed("svg-content-responsive", true);

        // set axes, as well as details on their ticks
        var xAxis = d3.svg.axis()
            .scale(x)
            .ticks(20)
            .tickSubdivide(true)
            .tickSize(6, 3, 0)
            .orient("bottom");

        var yAxis = d3.svg.axis()
            .scale(y)
            .ticks(20)
            .tickSubdivide(true)
            .tickSize(6, 3, 0)
            .orient("left");

        // group that will contain all of the plots
        var groups = svg.append("g").attr("transform", "translate(" + margin.l + "," + margin.t + ")");

        // style the circles, set their locations based on data
        var circles = groups.selectAll("circle.baseball")
            .data(players)
            .enter().append("circle")
            .attr("class", "circles")
            .attr({
                cx: function(d) { return x(+d[options.optionX]); },
                cy: function(d) { return y(+d[options.optionY]); },
                r: function(d) { return r(+d[options.optionR]); },
                id: function(d) { return d.Name; }
            })
            .style("fill", function(d) { return color(d[options.optionC]); });


        var information = {};

        // what to do when we mouse over a bubble
        var mouseOn = function() { 
            var circle = d3.select(this);

            // transition to increase size/opacity of bubble
            circle.transition()
                .duration(800).style("opacity", 1)
                .attr("r", 16).ease("elastic");

            // append lines to bubbles that will be used to show the precise data points.
            // translate their location based on margins
            svg.append("g")
                .attr("class", "guide")
                .append("line")
                .attr("x1", circle.attr("cx"))
                .attr("x2", circle.attr("cx"))
                .attr("y1", +circle.attr("cy") + 26)
                .attr("y2", h - margin.t - margin.b)
                .attr("transform", "translate(40,20)")
                .style("stroke", circle.style("fill"))
                .transition().delay(200).duration(400)
                .styleTween("opacity", function() { return d3.interpolate(0, .5); })

            svg.append("g")
                .attr("class", "guide")
                .append("line")
                .attr("x1", +circle.attr("cx") - 16)
                .attr("x2", 0)
                .attr("y1", circle.attr("cy"))
                .attr("y2", circle.attr("cy"))
                .attr("transform", "translate(40,30)")
                .style("stroke", circle.style("fill"))
                .transition().delay(200).duration(400)
                .styleTween("opacity", function() { return d3.interpolate(0, .5); });

            // function to move mouseover item to front of SVG stage, in case
            // another bubble overlaps it
            d3.selection.prototype.moveToFront = function() { 
                return this.each(function() { 
                    this.parentNode.appendChild(this); 
                }); 
            };

            $("#info").html(information[this.id]);
        };


        // what happens when we leave a bubble?
        var mouseOff = function() {
            var circle = d3.select(this);

            // go back to original size and opacity
            circle.transition()
                .duration(800).style("opacity", .5)
                .attr("r", function(d) { return r(+d[options.optionR]); }).ease("elastic");

            // fade out guide lines, then remove them
            d3.selectAll(".guide").transition().duration(100)
                .styleTween("opacity", function() { return d3.interpolate(.5, 0); })
                .remove()
            // $("#info").html("");
        };

        // run the mouseon/out functions
        circles.on("mouseover", mouseOn);
        circles.on("mouseout", mouseOff);

        // tooltips (using jQuery plugin tipsy)
        circles.append("title").text(function(d) {
            console.log(d);
            information[d.Name] = d.Name+"<br>Team: "+d.Team+"<br>Height: "+d.Height+"<br>Weight: "+d.Weight+"<br>Batting Average: "+d.Average+"<br>Home Runs: "+d.Homeruns+"<br>On-base Percentage: "+d.OBP;
            return d.Name; 
        })

        $(".circles").tipsy({ gravity: 's', });
        colorSet = []
        var colorArray = [];
        $.each(players, function (key, value) {
            if(jQuery.inArray(value[options.optionC],colorSet) == -1){
                colorSet.push(value[options.optionC]);
                colorArray.push({tempColor: value[options.optionC]});
            }
        });
        colorArray.sort(function(a, b) { return d3.ascending(a.tempColor, b.tempColor); })

        // the legend color guide
        var legend = svg.selectAll("rect")
            .data(colorArray)
            .enter().append("rect")
            .attr({
                x: function(d, i) { return (160 + i*30); },
                y: h,
                width: 25,
                height: 12
            })
            .style("fill", function(d) { return color(d.tempColor); });

        // legend labels    
        svg.selectAll("text")
            .data(colorArray)
            .enter().append("text")
            .attr({
                x: function(d, i) { return (160 + i*30); },
                y: h + 24,
            })
            .text(function(d) { return d.tempColor; });

        svg.append("text")
            .attr("class", "color label")
            .attr("text-anchor", "end")
            .attr("x", w/4)
            .attr("y", h+10)
            .text("Color: "+options.optionC);

        // draw axes and axis labels
        svg.append("g")
            .attr("class", "x axis")
            .attr("transform", "translate(" + margin.l + "," + (h - 60 + margin.t) + ")")
            .call(xAxis);

        svg.append("g")
            .attr("class", "y axis")
            .attr("transform", "translate(" + margin.l + "," + margin.t + ")")
            .call(yAxis);

        svg.append("text")
            .attr("class", "x label")
            .attr("text-anchor", "end")
            .attr("x", w + 50)
            .attr("y", h - margin.t - 5)
            .text(options.optionX);

        svg.append("text")
            .attr("class", "y label")
            .attr("text-anchor", "end")
            .attr("x", -20)
            .attr("y", 45)
            .attr("dy", ".75em")
            .attr("transform", "rotate(-90)")
            .text(options.optionY);
    }

    $("#update").append(document.lastModified);
});
