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
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 1) {
    rotateRead(pos);  
    if(isFull()){
      printData();
      }                  
  }

  for (int pos = 180; pos >= 0; pos -= 1) {
    rotateRead(pos);
    if(isFull()){
      printData();
    }                    
  }
}

int cacluateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void rotateRead(int pos){
  myservo.write(pos);
  distance = cacluateDistance();
  //Queues distance reading
  enqueue(distance, pos);
  //print angle
  //Serial.println(pos);
  delay(15);      
}

void printData(){
  Temp* temp = dequeueAvg();
  int pos1 = temp->pos1;
  int pos2 = temp->pos2;
  int avg = temp->avg;
  if(1){
    Serial.println("%d,%d,%d,%d\n", pos, pos1, pos2, avg); //Using Comma Serparated Values for easy parsing
  }
  free(temp);
}