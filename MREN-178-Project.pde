IMPORTANT NOTICE!
PLEASE USE GRAPHICS CODE, AS THE NAME SUGGESTS IT DOES THE GRAPHICS!!!

######################################
This is a version of the code used for testing, not to be run
#########################################


// //A more optimized version of the radar sketch
// //It should be more efficient hopefully this will imporve the performance of the sketch
// // and animation quality

// import processing.serial.*;

// Serial SerialPort;
// int lineLength = 600;
// float angle;
// float objectDistance; 

// void setup() {
//   printArray(Serial.list());
//   SerialPort = new Serial(this, Serial.list()[0], 115200);
//   SerialPort.bufferUntil('\n');
//   delay(1000);
//   SerialPort.clear();
//   SerialPort.write("0"); 
//   size(1200, 600);
//   background(0);
// }

// void draw(){
//   fill(0, 20);
//   noStroke();
//   rect(0, 0, width, height);
  
//   drawRadar();
//   drawObject();
//   drawAngleDisplay(); // 🔹 New angle bar display
//   delay(10);
// }

// void drawRadar() {
//   translate(width / 2, height);
//   stroke(0, 255, 0);
//   noFill();

//   // Draw radar circles with distance labels
//   for (int r = 100; r <= 600; r += 100) {
//     ellipse(0, 0, r * 2, r * 2);
    
//     // Draw distance markers
//     fill(0, 255, 0);
//     textSize(16);
//     textAlign(CENTER, CENTER);
//     text(r / 6 + " cm", r, -5);
//   }

//   // Draw static radar lines
//   line(0, 0, 0, -600);
//   line(0, 0, -lineLength * cos(PI / 6), -lineLength * sin(PI / 6));
//   line(0, 0, lineLength * cos(PI / 6), -lineLength * sin(PI / 6));

//   // 🔹 Use pushMatrix/popMatrix to rotate sweeping line
//   pushMatrix();
//   rotate(angle);  
//   stroke(0, 255, 0);
//   strokeWeight(2);
//   line(0, 0, lineLength, 0);
//   popMatrix();
// }

// void drawObject(){
//   if (objectDistance > 0) {
//     float rx = map(objectDistance, 0, 100, 0, 1200); 
//     float ry = map(objectDistance, 0, 100, 0, 600);
//     float objX = rx * cos(angle); 
//     float objY = -ry * sin(angle);
//     stroke(255, 0, 0);
//     fill(255, 0, 0);
//     ellipse(objX, objY, 10, 10);
//   }
// }

// // 🔹 New function to draw the angle bar
// void drawAngleDisplay() {
//   fill(0);
//   rect(0, height - 50, width, 50); // Black bar at the bottom
//   fill(0, 255, 0);
//   textSize(30);
//   textAlign(CENTER, CENTER);
//   text("Angle: " + degrees(angle) % 360 + "°", width / 2, height - 25);
// }

// void serialEvent(Serial SerialPort){
//   String data = SerialPort.readStringUntil('\n'); 
//   if (data != null) {
//     data = trim(data);
//     String[] input = split(data, ",");
//     angle = radians(float(input[0])); 
//     objectDistance = float(input[1]); 
//     println("Received servo angle: " + degrees(angle) + "°");
//     println("Received distance: " + objectDistance + " cm");
//   }
// }
