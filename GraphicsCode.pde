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

void serialEvent(Serial myport){// start reading data from the Serial port
    // reads the data from the Serial port up to the character '.' and puts it into the String variable "data".
    data = myPort.readStringUntil('.');
    data = data.substring(0,data.length()-1);
    index1 = data.indexOf(",");//finds the comma in the data
}

void drawRadar(){
    pushMatrix();//push the current transformation matrix onto the matrix stack
    translate(WIDTH/2, HEIGHT/2);//translate to the center of the canvas
    noFill();
    strokeWeight(2);
    stroke(98,245,31);//green color
    arc()
}

/*
int lineLength = 600;


void setup() {
  size(800, 600);  // Create a 600x600 window
  background(0);   // Black background
}

void draw(){
  drawRadar();
}

void drawRadar() {
  background(0);  // Clear the screen each frame
  translate(width/2, height);  // Move origin to bottom center
  
  // Draw radar circles
  stroke(0, 255, 0);
  noFill();
  for (int r = 100; r <= 600; r += 100) {
    ellipse(0, 0, r*2, r*2);
  }
  
  // Draw radar lines
  line(0, 0, 0, -600);
  line(0, 0, -lineLength*cos(PI/6), -lineLength*sin(PI/6));
  line(0, 0, lineLength*cos(PI/6), -lineLength*sin(PI/6));

  // Example sweeping line (will be controlled by sensor data later
  float angle = radians(frameCount % 360);
  if(angle < PI){
    float x = lineLength * cos(angle);
    float y = -lineLength * sin(angle);
    stroke(0, 255, 0);
    line(0, 0, x, y);
  }else if (angle > PI){
    angle = PI - (angle - PI);
    float x = lineLength * cos(angle);
    float y = -height * sin(angle);
    stroke(0, 255, 0);
    line(0, 0, x, y);
  }
}

//void scan(){
//  float angle = radians(frameCount % 180);
//  while (angle < 180){
//    float x = lineLength * cos(angle);
//    float y = -lineLength * sin(angle);
//  }
//}

*/