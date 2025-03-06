// This is the code that should take input from the serial monitor (we control that output) and use it to create graphics!

import processing.serial.*;//Library for serial communication
import java.awt.event.KeyEvent;//Library for detecting key presses (reading the serail data?)
import java.io.IOException;//Library for input/output functions

Serial myPort;  // Create object from Serial class

//Variables:
const int WIDTH = 1920;
const int HEIGHT = 1080;
boolean serialAvailable = false;
char val;
int ledPin = 13;
boolean ledState = false;
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;

void setup(){
    String portName = Serial.list()[0];//change the 0 to a 1 or 2 etc. to match your port
    myPort = new Serial(this, portName, 9600);
    myPort.bufferUntil('.');//Should read the serail up to.
    size(WIDTH, HEIGHT);
    smooth();
    establishContact();
}

void draw(){
    fill (98,245,31);
    noStroke();
    fill(0,4);
    rect(0, 0, WIDTH, 1010);
    fill(98,245,31);
    drawRadar();
    drawLine();
    drawObject();
    drawText();
}

void drawRadar(){
    pushMatrix();//push the current transformation matrix onto the matrix stack
    translate(WIDTH/2, HEIGHT/2);//translate to the center of the canvas
    noFill();
    strokeWeight(2);
    stroke(98,245,31);//green color
    arc()
}