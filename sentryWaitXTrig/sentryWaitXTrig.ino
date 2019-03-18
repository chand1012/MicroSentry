#include <Servo.h>
#define XPIN 10
#define TRIGPIN 9
#define BAUD 115200
#define TDELAY 10 // in ms
#define STEP 1
#define STOP 0
#define LEFT 1
#define RIGHT 2

Servo xservo;
Servo trigservo;

unsigned long lasttime = millis();
unsigned int xstate = 0;
unsigned int xpos = 90;
unsigned int trigstate = 0;
unsigned int trigpos = 100;
String command = "00"; //String Format: "<move><trig>" ie move right and shoot would be 21
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
        /*
        Serial.println(xpos);
        Serial.println(trigpos);
        Serial.println(xstate);
        Serial.println(trigstate);
        */
    }
    xstate = command.charAt(0) - '0';
    trigstate = command.charAt(1) - '0';
    if (xstate == RIGHT && lasttime<=millis() && xpos<=180){
        xpos += STEP;
        lasttime = millis() + TDELAY;
    } else if (xstate == LEFT && lasttime<=millis() && xpos>=0){
        xpos -= STEP;
        lasttime = millis() + TDELAY;
    }
    if (trigstate != 0) {
        lasttime = millis() + TDELAY;
        trigpos = 0;
    } else if (trigstate == 0 && lasttime<=millis()) {
        trigpos = 100;
    }
    xservo.write(xpos);
    trigservo.write(trigpos);
    //Serial.println(xservo.read());
    //Serial.println(trigservo.read());
    
} 