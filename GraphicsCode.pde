import processing.serial.*; // Import the serial library for comunicating with the Arduino

Serial SerialPort; // Creates a serial prot object, to communicate with the Arduino

int lineLength = 600; // Length of the radar sweeping line, value was chosen arbitrarily

// Dynamic lists for visualization effects, like fading and object persistance
ArrayList<PVector> trail = new ArrayList<>();  // Creates a dynamic array that data of type "PVector" which is a built in class in java/pocessing
ArrayList<Float> opacities = new ArrayList<>();  // Stores the opacities of the radar lines
ArrayList<PVector> detectedObjects = new ArrayList<>(); //Sotres the positions of detected objects
ArrayList<Float> objectOpacities = new ArrayList<>(); // To store opacity for fading effect
ArrayList<Float> objectTimestamps = new ArrayList<>(); // To store the time each object was detected

// Position varaibles for radar graphics
float x; 
float y;
//The servo angle
float angle;
// Distance of the object, value from Arduino
float objectDistance; 
// Variables used for the cacluation of middle points to represent objects as single points
float logDistance; // Middle distance
float distance1; // Distance of the first edge of object
float distance2; // Distance of the last detected edge of the object
//State variables that aid in the construction of the middle calculation logic 
boolean object1 = false; // If the first edge was detected
boolean object2 = false; // If the second/final edge was detected
// Variables for midle angle calculations
float objectMiddleAngle; // caclulated middle angle
float angle1; // the angle of the first edge
float angle2; // that angle of the second/ final edge

//NOTE: Edge here is classified as the first or last reading before/after the radar reading 0
// This approach assumes there a noticable gap between subsequent objects


// Fading parameters
float fadeStartTime = 1500; // Start fading after 1.5 seconds
float fadeDuration = 2000; // Fade over 2 seconds
float objectLifetime = fadeStartTime + fadeDuration; // Total time before object disappears


void setup() {
  //Setup Serial Communication
  printArray(Serial.list());
  SerialPort = new Serial(this, Serial.list()[0], 115200); // Open the port that the Arduino is on
  SerialPort.bufferUntil('\n'); // Sreal read line by line
  delay(3000); // Wait for the serial connection to establish
   // Wait for the serial connection to establish
  SerialPort.clear(); // Clear the serial buffer
  SerialPort.write("0"); // Send a command to the Arduino to start sending data
  size(1200, 600); // Window size is 1200px wide and 600px tall
  background(0);// Clear the background
}

void draw(){
  //Fading effect overlay:
  fill(0, 20); // Semi-transparent black
  noStroke();
  rect(0, 0, width, height); // Cover entire screen
  
  //Draw radar fixed lines and sweeping line
  drawRadar();
  // Draw the object on the radar
  drawObject(); 
  //Check is a key is pressed and the correspoinding action, here it is used to clear opbjects

  updateObjectFading();
}

void updateObjectFading() {
  // Get current time
  float currentTime = millis();
  
  // Iterate backwards through objects to safely remove them
  for (int i = detectedObjects.size() - 1; i >= 0; i--) {
    float age = currentTime - objectTimestamps.get(i);
    
    if (age > objectLifetime) {
      // Remove expired objects
      detectedObjects.remove(i);
      objectOpacities.remove(i);
      objectTimestamps.remove(i);
    } else if (age > fadeStartTime) {
      // Calculate fade amount (0 to 1)
      float fadeAmount = (age - fadeStartTime) / fadeDuration;
      // Update opacity (255 to 0)
      objectOpacities.set(i, 255 * (1 - fadeAmount));
    }
  }
}

void drawRadar() {
  //Move origin to eh bottom center of screen
  translate(width/2, height);
  
  // Draw radar circles
  stroke(0, 255, 0); // green
  noFill();
  //Draw circles at 100px intervals
  for (int r = 100; r <= 600; r += 100) {
    ellipse(0, 0, r*2, r*2);
  }
  
  // Draw static radar lines
  // 30 degrees both ways from vertical
  line(0, 0, 0, -600);
  line(0, 0, -lineLength*cos(PI/6), -lineLength*sin(PI/6));
  line(0, 0, lineLength*cos(PI/6), -lineLength*sin(PI/6));

  // Calculate and draw current sweeping line position
  if(angle < PI){
    //initial 0 - 180 degrees
    float x = lineLength * cos(angle);
    float y = -lineLength * sin(angle);
    stroke(0, 255, 0);
    strokeWeight(2);
    line(0, 0, x, y);
  }else if (angle > PI){
    // bounce back, match servo movement
    angle = PI - (angle - PI);
    float x = lineLength * cos(angle);
    float y = -height * sin(angle);
    stroke(0, 255, 0);
    strokeWeight(2);
    line(0, 0, x, y);
  }
  
  // Add current position to trail
  trail.add(new PVector(x, y));
  opacities.add(255.0);  // Start with full opacity
  
  // Draw the fading trail
  for (int i = 0; i < trail.size(); i++) {
    PVector p = trail.get(i);
    float alpha = opacities.get(i);
    //Style trail segments
    stroke(0, 255, 0, alpha);
    strokeWeight(map(dist(0, 0, p.x, p.y), 0, lineLength, 1, 5)); // Increase thickness outward
    line(0, 0, p.x, p.y);
    
    // Reduce opacity for fading effect
    opacities.set(i, alpha - 5); // Adjust the decrement value for faster/slower fade
  }

  // Remove fully transparent points
  while (!opacities.isEmpty() && opacities.get(0) <= 0) { // Remove the first element if it's fully transparent
    trail.remove(0); // Remove the first element
    opacities.remove(0); // Remove the first element
  }
}
/* The next step is to use the incoming serial data to dictate the position of the sweeping line. */

void drawObject(){
  // OBJECT POINT TRACING MODE (LEAVE THIS LINE COMMENTED OUT)
  if(objectDistance > 0){// Map the distance to the radar radius
    objectDistance = map(objectDistance, 0, 50, 0, 600); // Map the distance to the radar radius
    if(objectDistance > 0 && objectDistance < 1200){
      float objX = objectDistance * cos(angle); // Calculate the x position of the object
      float objY = objectDistance * -sin(angle); // Calculate the y position of the object
      stroke(255, 0, 0); // Set the stroke color to red
      fill(255, 0, 0); // Set the fill color to red
      ellipse(objX, objY, 10, 10); // Draw the object as a small circle
      detectedObjects.add(new PVector(objX, objY));
      objectOpacities.add(255.0);
      objectTimestamps.add((float)millis());
    }
  }
  for (int i = 0; i < detectedObjects.size(); i++) {
    PVector obj = detectedObjects.get(i);
    float opacity = objectOpacities.get(i);
    
    stroke(255, 0, 0, opacity);
    fill(255, 0, 0, opacity);
    ellipse(obj.x, obj.y, 10, 10);
  }

  //MIDDLE POINT SINGLE PING OPERATION MODE (LEAVE THIS LINE COMMENTED OUT)
  //Detect object start
  // if (!object1 && objectDistance > 0 && objectDistance <= 50) {
  //   distance1 = objectDistance;
  //   angle1 = angle; // Store the start angle
  //   object1 = true; // Trigger detection flag
  // } else if (object1 && !object2 && objectDistance <= 0) { // Detect object end
  //   distance2 = distance1;  // Use last valid distance //TODO: Fix this!
  //   angle2 = angle; // Store end angle
  //   object2 = true; // Trigger detection flag
  // }
  // // Compute middle and draw
  // if (object1 && object2) {
  //   //Calculate values for the middle of the object
  //   objectMiddleAngle = (angle1 + angle2) / 2; //Middle angle
  //   logDistance = (distance1 + distance2) / 2; // Middle distance
  //   logDistance = map(logDistance, 0, 50, 0, 600); // Scale the distance

  //   // Draw the middle of the object
  //   if (logDistance > 0 && logDistance < 600) {
  //     float objX = logDistance * cos(objectMiddleAngle);
  //     float objY = logDistance * -sin(objectMiddleAngle);
  //     //Represents the object as a red dot
  //     stroke(255, 0, 0);
  //     fill(255, 0, 0);
  //     ellipse(objX, objY, 10, 10);147
  //     //Add to the list of detected object to allow for clearing later
  //     detectedObjects.add(new PVector(objX, objY));
  //   }

  //   // Reset for next object
  //   object1 = false;
  //   object2 = false;
  // }
  // //Draw all the objects in the list
  // for (PVector obj : detectedObjects) {
  //   stroke(255, 0, 0);
  //   fill(255, 0, 0);
  //   ellipse(obj.x, obj.y, 10, 10);
  // }
}

// Function that handles recivining sensor data from arduino
void serialEvent(Serial SerialPort){
  //Read until a new line charater is detected
  String data = SerialPort.readStringUntil('\n');
  if(data != null){ // If there is data available then:
    data = trim(data); //Clean up the data, removing the white spaces
    String[] input = split(data, ","); // Split the data into an array of strings
    angle = radians(float(input[0]));
    objectDistance = float(input[1]); // The distance of the object from the radar
    //Debugging statements:
    //println("Recieved servo angle: " + angle);
    //println("Recived Avg: "+ objectDistance); // Print the angle to the console
  }
}
//Key press hadneiling and clearing object dots/pings
void keyPressed() {
  if (key == 'c') {
    detectedObjects.clear(); // Wipe all objects
    objectOpacities.clear();
    objectTimestamps.clear();
  }
}