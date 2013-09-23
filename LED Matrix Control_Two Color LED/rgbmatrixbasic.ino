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

void setup()
{
    pinMode (CSn, OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);
}

void loop()
{
//  OneLed();
//  SetLed();
//  delay(2000);
//  
//  TwoLed();
//  SetLed();
//  delay(2000);
//  
  NineLedInitialize();
  while(1) {
    NineLedLoop();
    SetLed();
    delay(1000);
  }
 // delay(2000);
}

void OneLed()
{
  ClearLed();
  color_buffer[27]=ColorRED;
}

void TwoLed()
{
  ClearLed();
  color_buffer[24]=ColorRED;
  color_buffer[31]=ColorGREEN;
}

void NineLedInitialize()
{
  ClearLed();
  //first column
  color_buffer[0]=ColorRED;
  color_buffer[3]=ColorREDGREEN;
  color_buffer[6]=ColorGREEN;
  //second column
  color_buffer[24]=ColorREDGREEN;
  color_buffer[27]=ColorGREEN;
  color_buffer[30]=ColorRED;
  //third column
  color_buffer[48]=ColorGREEN;
  color_buffer[51]=ColorRED;
  color_buffer[54]=ColorREDGREEN;
}

void NineLedLoop()
{
  int nine_index[] = {0,3,6,24,27,30,48,51,54};
  for (int i=0; i<9; i++) {
    color_buffer[nine_index[i]] = (color_buffer[nine_index[i]] + 1)%3 + 1;
  }
}

void ClearLed() {
  for (int i=0; i<64; i++) {
    color_buffer[i]=ColorBLACK;
  }
}

void SetLed()
{
    digitalWrite(CSn,LOW);
    delay(1);
    for (int bytenum = 0; bytenum < 64; bytenum++)
        SPI.transfer(color_buffer[bytenum]);
    delay(1);
    digitalWrite(CSn,HIGH);
}
