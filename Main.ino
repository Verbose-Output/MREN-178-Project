#include <Servo.h>
//#include "Queue.h"

// create servo object to control a servo
Servo myservo;  

// variable to store the servo position
int pos = 0;   
//Variables for the Ultrasonic Sensor:
const unsigned int trigPin = 10;
const unsigned int echoPin = 11;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // attaches the servo on pin 2 to the servo object
  myservo.attach(2);
  Serial.begin(9600);
  delay(5000);//5 second delay to guarentee that there is no loss of data before  
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);
    Serial.print(pos);      
    delay(20);                       
  }//The way the two for loops are written, there will be duplicate values of pos at the end of the loop
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    Serial.print(pos);          
    delay(20);                       
  }
  delay(10);
}

int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}
