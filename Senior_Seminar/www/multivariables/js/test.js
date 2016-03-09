d3.select("#viz")
                .selectAll("div")
                .data(xml.documentElement.getElementsByTagName("value"))
                .enter().append("div")
                  .style("width", function(d) { return d.textContent * 10 + "px"; })
                  .text(function(d) { return d.textContent; });
            // don't want dots overlapping axis, so add in buffer to data domain
              xScale.domain([d3.min(data, xValue)-1, d3.max(data, xValue)+1]);
              yScale.domain([d3.min(data, yValue)-1, d3.max(data, yValue)+1]);

              // x-axis
              svg.append("g")
                  .attr("class", "x axis")
                  .attr("transform", "translate(0," + height + ")")
                  .call(xAxis)
                .append("text")
                  .attr("class", "label")
                  .attr("x", width)
                  .attr("y", -6)
                  .style("text-anchor", "end")
                  .text("Calories");

              // y-axis
              svg.append("g")
                  .attr("class", "y axis")
                  .call(yAxis)
                .append("text")
                  .attr("class", "label")
                  .attr("transform", "rotate(-90)")
                  .attr("y", 6)
                  .attr("dy", ".71em")
                  .style("text-anchor", "end")
                  .text("Protein (g)");

              // draw dots
              svg.selectAll(".dot")
                  .data(data)
                .enter().append("circle")
                  .attr("class", "dot")
                  .attr("r", 3.5)
                  .attr("cx", xMap)
                  .attr("cy", yMap)
                  .style("fill", function(d) { return color(cValue(d));}) 
                  .on("mouseover", function(d) {
                      tooltip.transition()
                           .duration(200)
                           .style("opacity", .9);
                      tooltip.html(d["Cereal Name"] + "<br/> (" + xValue(d) 
                        + ", " + yValue(d) + ")")
                           .style("left", (d3.event.pageX + 5) + "px")
                           .style("top", (d3.event.pageY - 28) + "px");
                  })
                  .on("mouseout", function(d) {
                      tooltip.transition()
                           .duration(500)
                           .style("opacity", 0);
                  });

              // draw legend
              var legend = svg.selectAll(".legend")
                  .data(color.domain())
                .enter().append("g")
                  .attr("class", "legend")
                  .attr("transform", function(d, i) { return "translate(0," + i * 20 + ")"; });

              // draw legend colored rectangles
              legend.append("rect")
                  .attr("x", width - 18)
                  .attr("width", 18)
                  .attr("height", 18)
                  .style("fill", color);

              // draw legend text
              legend.append("text")
                  .attr("x", width - 24)
                  .attr("y", 9)
                  .attr("dy", ".35em")
                  .style("text-anchor", "end")
                  .text(function(d) { return d;})