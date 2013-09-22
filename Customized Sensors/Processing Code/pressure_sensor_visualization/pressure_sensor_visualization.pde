import processing.serial.*;

Serial myPort;

int w = 800;
int state;
int depth;

void setup()
{
  frame.setBackground(new java.awt.Color(0));
  println(Serial.list());
  //myPort = new Serial(this, "/dev/cu.usbmodemfd121", 9600);
  myPort = new Serial(this, "/dev/cu.usbserial-A9007TUp", 9600);
  size(w,w);
  background(0);
  frameRate(100);
}

void draw() {
  if (myPort.available() > 0) {
    state = myPort.read();
    depth = (int) map(state, 0, 255, 110, -5);
    depth = max(depth, 0);
    background(0);
    drawCurve(0,0,40-depth/5, depth);
  }
}

void drawCurve(int x, int y, int b, int d) {
  fill(60);
  rect(x,y,w-2*x,w);
  fill(168);
  smooth();
  noStroke();
  beginShape();
  vertex(x,y);
  bezierVertex(w/2-5*b, y, w/2-4*b, y, w/2-3*b, y+d/2);
  bezierVertex(w/2-2*b, y+d, w/2-b/4, y+d, w/2, y+d);
  bezierVertex(w/2+b/4, y+d, w/2+2*b, y+d, w/2+3*b, y+d/2);
  bezierVertex(w/2+4*b, y, w/2+5*b, y, w-x, y);
  endShape();
}
