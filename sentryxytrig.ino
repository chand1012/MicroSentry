// need to write the app for this
#include <Servo.h>
#define YPIN 11
#define XPIN 10
#define TRIGPIN 9

Servo yservo;
Servo xservo;
Servo trigservo;

unsigned int ypos = 90;
unsigned int xpos = 0;
unsigned int trigpos = 0;
String command = ""; //String Format: "<xangle><yangle><trig>" ie 0901001 for 90 degrees on x and 100 degrees on y and shoot
                     // where angle is 000 to 180

void setup(){
    xservo.attach(XPIN);
    trigservo.attach(TRIGPIN);
    yservo.attach(YPIN);
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
        ypos = command.substring(3,6).toInt();
        trigpos = command.substring(6).toInt();
      //  Serial.println(xpos);
        if (trigpos!=0){
            trigpos = 100;
        }
        //Serial.println(trigpos);
        xservo.write(xpos);
        yservo.write(ypos);
        trigservo.write(trigpos);
      	//Serial.println(xservo.read());
      //Serial.println(trigservo.read());
    }
}