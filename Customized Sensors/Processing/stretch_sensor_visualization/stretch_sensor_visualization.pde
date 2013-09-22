import processing.serial.*;

Serial myPort;

int d = 0;
int w = 1440;//800;
int l = 900;//700;
int delta = 1;
int fraction1;
int fraction2;
int toright;
int toleft;
int state;
int complete;

void setup()
{
  frame.setBackground(new java.awt.Color(128,128,128));
  println(Serial.list());
  myPort = new Serial(this, "/dev/cu.usbserial-A9007TUp", 9600);
  size(w,l);
  background(255);
  frameRate(20);
  d = 0;
}

void draw() {
  if (myPort.available() > 0) {
    d = myPort.read();
    println(d);
  }
  
  background(168);
  smooth();
  fill(60);
  noStroke();
  beginShape();
  vertex(d, 100);
  bezierVertex(w/2, 150-d/2, w/2, 150-d/2, w-d, 100);
  vertex(w-d, l-100);
  bezierVertex(w/2, l-150+d/2, w/2, l-150+d/2, d, l-100);
  endShape();
}
