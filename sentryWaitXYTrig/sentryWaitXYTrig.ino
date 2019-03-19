#include <Servo.h>
#define DEBUG false
#define XPIN 10
#define TRIGPIN 9
#define YPIN 11
#define TPOS 100 // in degrees
#define BAUD 115200 // in kbits
#define TDELAY 50 // in ms
#define STEP 1 // number of degrees per step
#define STOP 0
#define LEFT 1
#define RIGHT 2

Servo xservo;
Servo yservo;
Servo trigservo;

unsigned long lasttime = millis();
byte trigstate = 0;
byte xstate = 0;
byte ystate = 0;
byte xpos = 90;
byte ypos = 0;
byte trigpos = TPOS;
String command = "000"; //String Format: "<movex><movey><trig>" ie move right and shoot would be 21
                     // where move is 0, 1, or 2 and trig is 0 or 1

void setup(){
    xservo.attach(XPIN);
    trigservo.attach(TRIGPIN);
    Serial.begin(BAUD);
    while(!Serial){
        //need serial for operation
    }
    //Serial.println("Initialized.");
    //Serial.println("Starting primary function.");
}

void loop(){
    while (Serial.available() > 0){
        command = Serial.readString();        
    }
    if (millis()%1000==0 && DEBUG){
        Serial.println("x pos: " + String(xpos) + "y pos: " + String(ypos) + " trigpos: " + String(trigpos));
        Serial.println("Realtime X Pos: " + String(xservo.read()) + "Realtime Y Pos: " + String(yservo.read()) + " Realtime Trig Pos: " + String(trigservo.read()));
    }
    
    xstate = command.charAt(0) - '0';
    ystate = command.charAt(1) - '0';
    trigstate = command.charAt(2) - '0';
    if (xstate == RIGHT && lasttime<=millis() && xpos<180){
        xpos += STEP;
        lasttime = millis() + TDELAY;
    } else if (xstate == LEFT && lasttime<=millis() && xpos>0){
        xpos -= STEP;
        lasttime = millis() + TDELAY;
    }
    if (ystate == RIGHT && lasttime<=millis() && ypos>0){
        ypos += STEP;
        lasttime = millis() + TDELAY;
    } else if (ystate == LEFT && lasttime<=millis() && ypos<180){
        ypos -= STEP;
        lasttime = millis() + TDELAY;
    }
    if (trigstate != 0 && lasttime<=millis()) {
        lasttime = millis() + TDELAY;
        trigpos = 0;
    } else if (trigstate == 0 && lasttime<=millis()) {
        lasttime = millis() + TDELAY;
        trigpos = TPOS;
    }
    xservo.write(xpos);
    trigservo.write(trigpos);
    
    
} 