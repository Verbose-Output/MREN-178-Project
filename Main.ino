#include <Servo.h>
#include "Queue.h"

#define TRIGGER 1;

// create servo object to control a servo
Servo myservo;  

// variable to store the servo position
int pos = 0;    

//range finder
const int trigPin = 9;
const int echoPin = 10;

int distance;
long duration;

void setup() {
  // attaches the servo on pin 2 to the servo object
  myservo.attach(2);  
  //pinmode for range finder
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
    // 🔴 WAIT UNTIL '0' IS RECEIVED FROM PROCESSING 🔴
  while (true) {
    if (Serial.available() > 0) {
      char command = Serial.read();
      if (command == '0') {
        break;  // Exit loop when '0' is received
      }
    }
  }
  // delay(5000);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    rotateRead(pos);  
    if(isFull()){
      printData();
      }                  
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    rotateRead(pos);
    if(isFull()){
      printData();
    }                    
  }
}

int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void rotateRead(int pos){
  myservo.write(pos);
  distance = calculateDistance();
  //Queues distance reading
  enqueue(distance, pos);
  //print angle
  //Serial.println(pos);
  delay(15);      
}

void printData(){
  Temp* temp = dequeueAvg();
  // int pos1 = temp->pos1;
  // int pos2 = temp->pos2;
  int avg = temp->avg;
  
  // Remove unnecessary if statement and use proper formatting
  Serial.print(pos);
  Serial.print(",");
  Serial.println(avg);
  
  free(temp);
}