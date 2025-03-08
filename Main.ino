#include <Servo.h>
#include "Queue.h"

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
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(5);
}

int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}
//test5