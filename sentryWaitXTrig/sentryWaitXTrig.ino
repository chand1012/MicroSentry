#include <Servo.h>
#define XPIN 10
#define TRIGPIN 9

#define STOP 0
#define LEFT 1
#define RIGHT 2

Servo xservo;
Servo trigservo;

unsigned int xstate = 0;
unsigned int xpos = 0;
unsigned int trigstate = 0;
unsigned int trigpos = 0;
String command = ""; //String Format: "<move><trig>" ie move right and shoot would be 21
                     // where move is 0, 1, or 2

void setup(){
    xservo.attach(XPIN);
    trigservo.attach(TRIGPIN);
    Serial.begin(9600);
    while(!Serial){
        //need serial for operation
    }
    //Serial.println("Initialized.");
    //Serial.println("Starting primary function.");
}

void loop(){
    while (Serial.available() > 0){
        command = Serial.readString();
        //Serial.println("Command: "+command);
        xstate = command.substring(0,1).toInt();
        trigstate = command.substring(1).toInt();
      //  Serial.println(xpos);
        if (xstate == RIGHT){
            xpos++;
        } else if (xstate == LEFT){
            xpos--;
        }
        if (trigstate != 0) {
            trigpos = 100;
        } else {
            trigpos = 0;
        }
        //Serial.println(trigpos);
        xservo.write(xpos);
        trigservo.write(trigpos);
      	//Serial.println(xservo.read());
      //Serial.println(trigservo.read());
    }
} // needs tested