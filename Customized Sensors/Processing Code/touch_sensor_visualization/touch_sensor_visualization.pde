import processing.serial.*;

Serial myPort;

int w = 800;
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
  size(800,800);
  background(255);
  frameRate(100);
  
  complete = -1;
}

void draw() {
  while (complete < 3) {
    if (myPort.available() > 0) {
      state = myPort.read();
      if (state == 255) {
        complete = 0;
      }
      else if (complete == 0) {
        complete++;
        fraction1 = state;
      }
      else if (complete == 1) {
        complete++;
        fraction2 = state;
      }
      else if (complete == 2) {
        complete++;
        if (state == 1) {
          println("GOT A RIGHT SWIPE");
          toright = 0;
        }
        else if (state == 2) {
          println("GOT A LEFT SWIPE");
          toleft = w;
        }
      }
    }
  }
  
  print(fraction1);
  print(" ");
  println(fraction2);

  background(168);
  fill(60);
  noStroke();
  rect(0, 100, w, w-100);
  
  fill(30);
  rect(300, 0, 100, (int) (fraction1));
  rect(450, 0, 100, (int) (fraction2));

  fill(30);
  if (toright < w) {
    rect(toright,300,300,50);
    toright = toright + 200;
  }
  if (toleft + 300 > 0) {
    rect(toleft, 300, 300, 50);
    toleft = toleft - 200;
  }
  
  complete = -1;
}
