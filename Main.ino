#include <Servo.h>
#include "Queue.h"

// create servo object to control a servo
Servo myservo;  

// variable to store the servo position
int pos = 0;    

void setup() {
  Serial.begin(9600);
  delay(5000);//5 second delay to guarentee that there is no loss of data before 
  // attaches the servo on pin 2 to the servo object
  myservo.attach(2);  
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
