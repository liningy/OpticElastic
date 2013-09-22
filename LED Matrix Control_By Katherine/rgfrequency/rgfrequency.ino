#include <SPI.h>  // this forum strips off the angle brackets

// Connect to "Output SPI" JP4 on LED Matrix
// DIO 10 = CSn  (JP4-3)
// DIO 11 = MOSI (JP4-2)
// DIO 13 = SCK  (JP4-4)
//     5V = VCC  (JP4-5 or JP4-6)
//    GND = GND  (JP4-1)

const int CSn = 10;
const int ColorBLACK = 0;
const int ColorRED = 1;
const int ColorGREEN = 2;
const int ColorREDGREEN = 3;

int color_buffer[64];
int nine_index[] = {0,3,6,24,27,30,48,51,54};

float x = 1.0;
boolean keyboard = false;
int frequency_index = 0;
float frequency[] = {1.0, 20.0, 50.0, 100.0, 500.0};

//int ledPin = 13;

void setup()
{
    pinMode (CSn, OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);
  
    x = 1.0;
    Serial.begin(9600);
    
    //pinMode(ledPin, OUTPUT);
}

void loop()
{
  SetLed(ColorRED);
  //digitalWrite(ledPin, HIGH);
  delay(x);
  
  SetLed(ColorBLACK);
  //digitalWrite(ledPin, LOW);
  delay(x);
  
  if (keyboard) {
    if (Serial.available() > 0) {
      if(Serial.read() == 32) {      
        frequency_index = (frequency_index + 1) % 5;
      }
    }
    
    x = frequency[frequency_index];
  }
  else {
    x = x*1.05;
    if (x > 300) {
      x = 1.0;
    }
  }
}

void SetLed(int color)
{
  for (int i=0; i<9; i++) {
    color_buffer[nine_index[i]] = color;
  }

  digitalWrite(CSn,LOW);
  delay(1);
  for (int bytenum = 0; bytenum < 64; bytenum++)
      SPI.transfer(color_buffer[bytenum]);
  delay(1);
  digitalWrite(CSn,HIGH);
}
