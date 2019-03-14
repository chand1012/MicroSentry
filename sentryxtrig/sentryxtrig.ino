#include <Servo.h>
#define XPIN 10
#define TRIGPIN 9

Servo xservo;
Servo trigservo;

unsigned int xpos = 0;
unsigned int trigpos = 0;
String command = ""; //String Format: "<angle><trig>" ie 0901 for 90 degrees and shoot
                     // where angle is 000 to 180

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
        xpos = command.substring(0,3).toInt();
        trigpos = command.substring(3).toInt();
      //  Serial.println(xpos);
        if (trigpos!=0){
            trigpos = 100;
        }
        //Serial.println(trigpos);
        xservo.write(xpos);
        trigservo.write(trigpos);
      	//Serial.println(xservo.read());
      //Serial.println(trigservo.read());
    }
}