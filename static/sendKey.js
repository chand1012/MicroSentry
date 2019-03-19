var isKeyDown = false;
var xstate = 0;
var trig = 0;
var sendstring = "";
var lasttime = 0;
function doWork(trigstring, event){
    console.log(trigstring);
    $.post("/postrequest", {"byte":trigstring});
    if (event!=="undefined") {
        event.preventDefault();
    }    
}
function genSend(){
    return xstate.toString() + trig.toString();
}
       
$(window).keydown(function(event){
    if (!isKeyDown){
        isKeyDown = true
        if (event.keyCode == 37 ) { // left
            xstate = 1;
        } else if (event.keyCode == 39 ) { // right
            xstate = 2;
        }
        if (event.keyCode == 32){
            trig = 1;
        }
        sendstring = genSend();
        doWork(sendstring, event);
    }
});
$(window).keyup(function(event){
    isKeyDown = false;
    if (event.keyCode == 37 || event.keyCode == 39) { 
        xstate = 0;
    } 
    if (event.keyCode == 32){
        trig = 0;
    }
    sendstring = genSend();
    doWork(sendstring, event);
});
console.log("Script Loaded.");