// This is the code that should take input from the serial monitor (we control that output) and use it to create graphics!

import processing.serial.*;

Serial myPort;  // Create object from Serial class

//Variables:
const int WIDTH = 800;
const int HEIGHT = 600;
boolean serialAvailable = false;
char val;
int ledPin = 13;
boolean ledState = false;

void setup(){
    String portName = Serial.list()[0];//change the 0 to a 1 or 2 etc. to match your port
    myPort = new Serial(this, portName, 9600);
    size(WIDTH, HEIGHT);
    establishContact();
}

void draw(){

}
