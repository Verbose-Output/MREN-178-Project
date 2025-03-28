import processing.serial.*;

Serial SerialPort;
int lineLength = 600;
ArrayList<PVector> trail = new ArrayList<>();  // Creates a dynamic array that data of type "PVector" which is a built in class in java/pocessing
ArrayList<Float> opacities = new ArrayList<>();  // Stores their opacities

float x;
float y;
float angle;
float objectAngle; // Angle of the object
float objectDistance; // Distance of the object
int objectStart;
int objectEnd; // The distance of the object from the radar
int objectAvg; // The average of the two objects

void setup() {
  printArray(Serial.list());
  SerialPort = new Serial(this, Serial.list()[2], 115200); // Open the port that the Arduino is on
  SerialPort.bufferUntil('\n'); // Sreal read line by line
  delay(3000); // Wait for the serial connection to establish
   // Wait for the serial connection to establish
  SerialPort.clear(); // Clear the serial buffer
  SerialPort.write("0"); // Send a command to the Arduino to start sending data
  size(1200, 600);
  background(0);
}

void draw(){
  // Draw a translucent black overlay for fading effect
  fill(0, 20); // The lower the value, the longer the trail lingers
  noStroke();
  rect(0, 0, width, height);
  
  drawRadar();
  drawObject(); // Draw the object on the radar
  delay(10); // Adjust delay for smoother effect
}

void drawRadar() {
  translate(width/2, height);
  
  // Draw radar circles
  stroke(0, 255, 0);
  noFill();
  for (int r = 100; r <= 600; r += 100) {
    ellipse(0, 0, r*2, r*2);
  }
  
  // Draw static radar lines
  line(0, 0, 0, -600);
  line(0, 0, -lineLength*cos(PI/6), -lineLength*sin(PI/6));
  line(0, 0, lineLength*cos(PI/6), -lineLength*sin(PI/6));

  // Calculate current sweeping line position
  //float angle = radians(frameCount % 360);
  if(angle < PI){
    float x = lineLength * cos(angle);
    float y = -lineLength * sin(angle);
    stroke(0, 255, 0);
    strokeWeight(2);
    line(0, 0, x, y);
  }else if (angle > PI){
    angle = PI - (angle - PI);
    float x = lineLength * cos(angle);
    float y = -height * sin(angle);
    stroke(0, 255, 0);
    strokeWeight(2);
    line(0, 0, x, y);
  }
  
  // Add new position to trail
  trail.add(new PVector(x, y));
  opacities.add(255.0);  // Start with full opacity
  
  // Draw the fading trail
  for (int i = 0; i < trail.size(); i++) {
    PVector p = trail.get(i);
    float alpha = opacities.get(i);
    
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
  if(objectDistance > 0){// Map the distance to the radar radius
    float rx = map(objectDistance, 0, 100, 0, 1200); // Map the distance to the radar radius
    float ry = map(objectDistance, 0, 100, 0, 600); // Map the distance to the radar radius
    float objX = rx * cos(angle); // Calculate the x position of the object
    float objY = -ry * sin(angle); // Calculate the y position of the object
    stroke(255, 0, 0); // Set the stroke color to red
    fill(255, 0, 0); // Set the fill color to red
    ellipse(objX, objY, 10, 10); // Draw the object as a small circle
  }
}

void serialEvent(Serial SerialPort){
  String data = SerialPort.readStringUntil('\n'); //
  if(data != null){ // If there is data available then:
    data = trim(data); //Clean up the data, removing the white spaces
    String[] input = split(data, ","); // Split the data into an array of strings
    angle = radians(float(input[0])); // Convert the incoming data to a float and then to radians
    //angle = radians(float(data)); // Conver the incoming data to a float and then to radians
    objectDistance = float(input[1]); // The distance of the object from the radar
    println("Recieved servo angle: " + angle);
    println("Recived Avg: "+ objectDistance); // Print the angle to the console
  }
}

//TODO: Map the length to be 1 meter
//TODO:bject detection using the method
// TODO:Seperate pos and of servo and other data in terms of print so that they only print data when necissary
//TODO: Add distance tags to the radar screen