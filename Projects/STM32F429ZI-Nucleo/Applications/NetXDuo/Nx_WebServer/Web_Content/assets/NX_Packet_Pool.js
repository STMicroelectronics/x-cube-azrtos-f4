window.onload = function () {

var dataPoints = [];
var nx_url = "/GetNXPacket";

var options = {
	theme: "light2",
	title: {
		text: "NetX Packet Pool Available"
	},
	data: [{
		type: "spline",
		dataPoints: dataPoints
	}]
};

$("#chartContainer").CanvasJSChart(options);
addData();

// Initial Values
var xValue = 0;
var yValue = 10;

function addData(data) {
    jQuery.get(nx_url, function (num, status) {
			dataPoints.push({ x: xValue, y: parseInt(num)});
			xValue++;
			yValue = parseInt(num);
		}) 

	$("#chartContainer").CanvasJSChart().render();
	setTimeout(addData, 1500);
}

}