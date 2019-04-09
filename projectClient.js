function getTemperature() {
    // console.log("in get temperature");
    $.getJSON("http://localhost:1306/?temperature?1",
    (data, status) => {
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
        
        // there is another tag to indicate C or F
        // offset++;
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
    if(value == "stop") stopUpdate();
    if(value == "open") updateTemperature();
    
}
function stopUpdate() {
    clearInterval(timer);
}
function updateTemperature() {
    timer = setInterval(getTemperature,1000);
}

function switchingUnit() {
    var unit = $(this).attr('value');
    var res = $.get("http://localhost:1306/?unit?" + unit);
}
// $("#clickMe").click(getTemperature);
var stop = false;
var timer = setInterval(getTemperature, 60000);
var offset = 0;

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