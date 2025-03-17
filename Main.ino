#include <Servo.h>
#include "Queue.h"

#define TRIGGER = 1;

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
  myservo.attach(2);
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
  
    // Calculating the distance
    distance = duration * 0.034 / 2;
  
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);  
    
    //Queues distance reading
    enqueue(distance);

    //print angle
    serial.println(pos);

    delay(15);                       
  }

  for(int i = 0; i<45; i++){
    int k = dequeueAvg();
    if (k > TRIGGER){
      serial.println(k);
    }
  }

  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
  
    // Calculating the distance
    distance = duration * 0.034 / 2;
  
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);  
    
    //Queues distance reading
    enqueue(distance);

    //print angle
    serial.println(pos);


    delay(15);                       
  }
}
  
  for(int i = 0; i<45; i++){
    serial.println(dequeueAvg());
  }

int cacluateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}