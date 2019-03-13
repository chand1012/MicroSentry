#include <Servo.h>
#define XPIN 10
#define TRIGPIN 9
#define STARTCHAR "<"
#define ENDCHAR ">"

Servo xservo;
Servo trigservo;

unsigned int xpos = 0;
unsigned int spos = 0;
String command = ""; //String Format: "x:<angle>;trig:<1 or 0>;"

void setup(){
    xservo.attach(XPIN);
    trigservov.attach(TRIGPIN);
    Serial.begin(9600);
    while(!Serial){
        //need serial for operation
    }
    Serial.write("Initialized.\n");
    Serial.write("Starting primary function.\n");
}

void loop(){
    while (Serial.available() > 0){
        command = Serial.readString();
        
    }
}