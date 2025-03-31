#include <Servo.h>
#include "Queue.h"

// create servo object to control a servo
Servo myservo;  

// variable to store the servo position
int pos = 0;    

//pin defintions
const int trigPin = 9;
const int echoPin = 10;
//buffer size, make sure it matches SIZE in Queue.h
const unsigned int Size = 5;
//Variables for Ultrasonic distance sensor calculations
float distance;
long duration;

void setup() {
  // attaches the servo on pin 2 to the servo object
  myservo.attach(2);  
  //pinmode setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
    // WAIT UNTIL '0' IS RECEIVED FROM PROCESSING SKETCH
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
    //If the buffer is full, send out the calcualted average of the values in the buffer
    if (isFull()) {
      Temp* temp = dequeueAvg();
      if(temp->avg < 50){// Using 50cm as a reange limitaion to reduce unwanted noise
        Serial.println(temp->avg);
      }else{
        Serial.println("0");
      }
      free(temp);
    } else {
      // Should never happen since we enqueue the same amount of readings per pos as the size of the buffer
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


//Function to handle use of ultrasonic sensor 
float calculateDistance() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse with timeout (e.g., 30ms max)
  const unsigned long timeout = 30000; // Max time to wait for echo (µs)
  duration = pulseIn(echoPin, HIGH, timeout);

  // // Check if duration is valid (typical range: 150µs to 25ms for 3cm-4m)
  if (duration == 0 || duration > 25000) { 
    return 0; // No echo or out-of-range
  }

  // Convert to distance (cm)
  distance = (duration * 0.0343) / 2; 
  return distance;
}