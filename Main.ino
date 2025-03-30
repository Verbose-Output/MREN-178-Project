#include <Servo.h>
#include "Queue.h"

//#define TRIGGER 1;

// create servo object to control a servo
Servo myservo;  

// variable to store the servo position
int pos = 0;    

//range finder
const int trigPin = 9;
const int echoPin = 10;
const unsigned int Size = 5;
float distance;
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
}


void loop() {
  for (pos = 0; pos <= 180; pos++) {
    myservo.write(pos);  // Move servo to `pos`
    delay(20);  // Let servo settle
    
    // Take 5 readings (or more) per position
    for (int i = 0; i < SIZE; i++) {  
      distance = calculateDistance();
      enqueue(distance, pos);
      delay(10);  // Small delay between readings
    }

    // Print position & average (if available)
    Serial.print(pos);
    Serial.print(",");
    
    if (isFull()) {
      Temp* temp = dequeueAvg();
      if(temp->avg < 50){
        Serial.println(temp->avg);
      }else{
        Serial.println("0");
      }
      free(temp);
    } else {
      // Should never happen since we enqueue 5 readings per pos
      Serial.println("ERROR: Queue not full");
    }
  }

  // Repeat for reverse sweep (180 → 0)
  for (pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
    delay(20);
    
    for (int i = 0; i < SIZE; i++) {
      distance = calculateDistance();
      enqueue(distance, pos);
      delay(10);
    }

    Serial.print(pos);
    Serial.print(",");
    
    if (isFull()) {
      Temp* temp = dequeueAvg();
      if(temp->avg < 50){
        Serial.println(temp->avg);
      }else{
        Serial.println("0");
      }
      free(temp);
    } else {
      Serial.println("ERROR: Queue not full");
    }
  }
}

float calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
  delay(10);
}