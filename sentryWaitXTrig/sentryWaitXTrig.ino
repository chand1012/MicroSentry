#include <Servo.h>
#define XPIN 10
#define TRIGPIN 9
#define TPOS 100 // in degrees
#define BAUD 115200 // in kbits
#define XDELAY 50 // in ms
#define TRIGDELAY 1000
#define STEP 1 // number of degrees per step
#define STOP 0
#define LEFT 1
#define RIGHT 2

Servo xservo;
Servo trigservo;

unsigned long lasttime = millis();
unsigned long trigtime = millis();
byte trigstate = 0;
byte xstate = 0;
byte xpos = 90;
byte trigpos = TPOS;
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
    }
    /*
    if (millis()%1000==0){
        Serial.println("x pos: " + String(xpos) + " trigpos: " + String(trigpos));
        Serial.println("Realtime X Pos: " + String(xservo.read()) + " Realtime Trig Pos: " + String(trigservo.read()));
    }
    */
    xstate = command.charAt(0) - '0';
    trigstate = command.charAt(1) - '0';
    if (xstate == RIGHT && lasttime<=millis() && xpos<180){
        xpos += STEP;
        lasttime = millis() + XDELAY;
    } else if (xstate == LEFT && lasttime<=millis() && xpos>0){
        xpos -= STEP;
        lasttime = millis() + XDELAY;
    }
    if (trigstate != 0 && trigtime<=millis()) {
        trigtime = millis() + TRIGDELAY;
        trigpos = 0;
    } else if (trigstate == 0 && trigtime<=millis()) {
        trigtime = millis() + TRIGDELAY;
        trigpos = TPOS;
    }
    xservo.write(xpos);
    trigservo.write(trigpos);

} 