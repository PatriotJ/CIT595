function getTemperature() {
    // console.log("in get temperature");
    $.getJSON("http://localhost:1306/?temperature?1",
    (data, status) => {
        if(data.connect != 1) {
            $("#temperature").html("Arduino not connected");
            $("#max").html("Arduino not connected");
            $("#min").html("Arduino not connected");
            $("#avg").html("Arduino not connected");
        }
        else {
            // console.log(data);
            $("#temperature").html(data.temperature + offset);
            $("#max").html(data.max_temp+ offset);
            $("#min").html(data.min_temp+ offset);
            $("#avg").html(data.avg_temp+ offset);
            if(data.celsius == 0) {
                $('.unit').html("F");
            }
            else if(data.celsius == 1) {
                $('.unit').html("C");
            }
            // there should be another tag to show whether sensor is connected or not
            // there is another tag to indicate C or F
            // offset++;
        }
    });
}
function changeLightColor() {
    // var color = $.value;
    // console.log(color);
    // console.log($(this).attr("value"));
    var color = $(this).attr("value");
    var res = $.get("http://localhost:1306/?light?" + color+"?");
}
function arduinoControl() {
    var value = $(this).attr("value");
    // console.log(value);
    if(value == "stop") {
        stopUpdate();
        var res = $.get("http://localhost:1306/?reading?stop?");
    }
    if(value == "open") {
        updateTemperature();
        var res = $.get("http://localhost:1306/?reading?resume?");
    }
    
}
function stopUpdate() {
    clearInterval(timer);
}
function updateTemperature() {
    timer = setInterval(getTemperature,1000);
}

function switchingUnit() {
    var unit = $(this).attr('value');
    var res = $.get("http://localhost:1306/?unit?" + unit+"?");
}
function terminate() {
    console.log("in terminate method");
    var res = $.get("http://localhost:1306/?off?");
}

//author: cyj
function getWindChillTemperature() {
    $.getJSON("http://localhost:1306/?temperature?1",
    (data, status) => {
        var temperature = data.temperature + offset;
        var windSpeed = $("#windSpeed").val();
        if(data.celsius == 1) {
            temperature = (temperature-32)*5/9;
        }
        var wct = 35.74 + 0.6215*temperature - 35.75*Math.pow(windSpeed, 0.16) + 0.4275*temperature*Math.pow(windSpeed, 0.16);
        wct+=" F";
        $('#showWindChillTemperature').html(wct);
    });
}

//cyj
function recordTenTemperatures() {
    //get the current temperature and its unit
    var temp = $("#temperature").text();
    var unit = $(".unit").text();
    var currentTemperature = temp + " " + unit;
    //insert it into the TenTemperatures arrays
    while(TenTemperatures.length>=10) TenTemperatures.pop();
    TenTemperatures.splice(0,0,currentTemperature);
    //show the array on the web page
    for (var i = 0; i < currentTemperature.length; i++) {
        $("#.i"+i).html(currentTemperature[i]);
    }
}

// $("#clickMe").click(getTemperature);
var stop = false;
var timer = setInterval(getTemperature, 1000);
var offset = 0;
var timer2 = setInterval(recordTenTemperatures, 10000);
var TenTemperatures = [];

// color control
$("#blueLight").click(changeLightColor);
$("#redLight").click(changeLightColor);
$("#greenLight").click(changeLightColor);
$("#off").click(changeLightColor);
$("#random").click(changeLightColor);
$("#normal").click(changeLightColor);
// temperature update control
$(".arduinoControl").click(arduinoControl);
$(".unitsControl").click(switchingUnit);
$(".terminate").click(terminate);
//get wind chill temperature
$("#getWindChillTemperatureButton").click(getWindChillTemperature);