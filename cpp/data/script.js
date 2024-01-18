// Abrufen der aktuellen Sensorwerte beim Laden der Seite 
window.addEventListener('load', getReadings);




  
// Luftfeuchte Messung 1
var gaugeHum1 = new RadialGauge({
  renderTo: 'gauge-humidity1',
  width: 250,
  height: 250,
  units: "Bodenfeuchte (%)",
  minValue: 0,
  maxValue: 100,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100"

  ],
  minorTicks: 4,
  strokeTicks: true,
    highlights: [
        { from: 0, to: 10, "color": "#FE949A"  },
        { from: 10, to: 40, color:  "#BEFDA7" },
        { from: 40, to: 80,  "color": "#FE6970" },
        { from: 80, to: 100, "color": "#C94F4E" },

    ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();



// Luftfeuchte Messung 2
var gaugeHum2 = new RadialGauge({
  renderTo: 'gauge-humidity2',
  width: 250,
  height: 250,
  units: "Bodenfeuchte (%)",
  minValue: 0,
  maxValue: 100,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100"

  ],
  minorTicks: 4,
  strokeTicks: true,
    highlights: [
        { from: 0, to: 15, "color": "#FE949A" },
        { from: 15, to: 50, color: "#BEFDA7" },
        { from: 50, to: 80,  "color": "#FE6970" },
        { from: 80, to: 100, "color": "#C94F4E" },

    ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();


// Luftfeuchte Messung 3
var gaugeHum3 = new RadialGauge({
  renderTo: 'gauge-humidity3',
  width: 250,
  height: 250,
  units: "Bodenfeuchte (%)",
  minValue: 0,
  maxValue: 100,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100"

  ],
  minorTicks: 4,
  strokeTicks: true,
    highlights: [
        { from: 0, to: 20, "color": "#FE949A" },
        { from: 20, to: 60, color: "#BEFDA7" },
        { from: 60, to: 80,  "color": "#FE6970" },
        { from: 80, to: 100, "color": "#C94F4E" },

    ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();










// Funktion, um aktuelle Messwerte auf der Webseite zu erhalten, wenn sie zum ersten Mal geladen wird
function getReadings(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);

      var hum1 = myObj.humidity1;
      var hum2 = myObj.humidity2;
      var hum3 = myObj.humidity3;
      var stat1 = myObj.STATE;

      gaugeHum1.value = hum1;
      gaugeHum2.value = hum2;
      gaugeHum2.value = hum3;
      alarm1 = stat1;
    }
  }; 
  xhr.open("GET", "/readings", true);
  xhr.send();
}

if (!!window.EventSource) {
  var source = new EventSource('/events');
  
  source.addEventListener('open', function(e) {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) {
    if (e.target.readyState != EventSource.OPEN) {
      console.log("Events Disconnected");
    }
  }, false);
  
  source.addEventListener('message', function(e) {
    console.log("message", e.data);
  }, false);
  
  source.addEventListener('new_readings', function(e) {
    console.log("new_readings", e.data);
    var myObj = JSON.parse(e.data);
    console.log(myObj);

    gaugeHum1.value = myObj.humidity1;
    gaugeHum2.value = myObj.humidity2;
    gaugeHum3.value = myObj.humidity3;
    alarm1 = myObj.STATE;
  }, false);
}