int lineLength = 600;

ArrayList<PVector> trail = new ArrayList<>();  // Creates a dynamic array that data of type "PVector" which is a built in class in java/pocessing
ArrayList<Float> opacities = new ArrayList<>();  // Stores their opacities

float x;
float y;

void setup() {
  size(800, 600);
  background(0);
}

void draw(){
  // Draw a translucent black overlay for fading effect
  fill(0, 20); // The lower the value, the longer the trail lingers
  noStroke();
  rect(0, 0, width, height);
  
  drawRadar();
  delay(20); // Adjust delay for smoother effect
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
  float angle = radians(frameCount % 360);
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
    opacities.set(i, alpha - 5);
  }

  // Remove fully transparent points
  while (!opacities.isEmpty() && opacities.get(0) <= 0) {
    trail.remove(0);
    opacities.remove(0);
  }

  // Draw the main sweeping line
  //stroke(0, 255, 0);
  //strokeWeight(2);
  //line(0, 0, x, y);
}
