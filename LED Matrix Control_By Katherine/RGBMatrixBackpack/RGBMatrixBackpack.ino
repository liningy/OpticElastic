// Writing to the RGB Serial Backpack Matrix from SparkFun Electronics
// by Ryan Owens
// Copyright SparkFun Electronics

//Define the "Normal" Colors
#define BLACK  0
#define RED  0xE0
#define GREEN  0x1C
#define BLUE  0x03
#define ORANGE  RED|GREEN
#define MAGENTA  RED|BLUE
#define TEAL  BLUE|GREEN
#define WHITE (RED|GREEN|BLUE)-0xA0

//Define the SPI Pin Numbers
#define DATAOUT 11//MOSI
#define DATAIN  12//MISO 
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss

//Define the variables we'll need later in the program
char color_buffer [64];
int light[25];

void setup() 
{  
  //SPI Bus setup
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	//Enable SPI HW, Master Mode, divide clock by 16    //SPI Bus setup
  
  //Set the pin modes for the RGB matrix
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  
  //Make sure the RGB matrix is deactivated
  digitalWrite(SLAVESELECT,HIGH);
  
  //Set up the mux selector and reader pins
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
} 
 
void loop() 
{
  //Determine which points are being touched.
  for (int j=0; j<25; j++) {
    int i = j%16;
    if (i%2) {
      digitalWrite(A2, HIGH);
    }
    else {
      digitalWrite(A2, LOW);
    }
    i = i >> 1;
    if (i%2) {
      digitalWrite(A3, HIGH);
    }
    else {
      digitalWrite(A3, LOW);
    }
    i = i >> 1;
    if (i%2) {
      digitalWrite(A4, HIGH);
    }
    else {
      digitalWrite(A4, LOW);
    }
    i = i >> 1;
    if (i%2) {
      digitalWrite(A5, HIGH);
    }
    else {
      digitalWrite(A5, LOW);
    }
    if (j < 16) {
      light[j] = analogRead(A0);
    }
    else {
      light[j] = analogRead(A1);
    }
  }
  
  //Load colors into the first row color buffer array. 
  //This will be the array of colors sent to the RGB matrix.
  for (int i=0; i<64; i++) {
    if (i%8 < 5 && i/8 < 5) {
      if (light[i/8*5 + i%8] > 900) {
        color_buffer[i] = RED;
      }
      else {
        color_buffer[i]=BLUE;
      }
    }
    else {
      color_buffer[i]=BLACK;
    }
  }
  
  //Activate the RGB Matrix
  digitalWrite(SLAVESELECT, LOW);
  //Send the color buffer to the RGB Matrix
  for(int LED=0; LED<64; LED++){
    spi_transfer(color_buffer[LED]);
  }
  //Deactivate the RGB matrix.
  digitalWrite(SLAVESELECT, HIGH);
  //while(1);
  delay(100); // allow some time for the Serial data to be sent 
} 

//Use this command to send a single color value to the RGB matrix.
//NOTE: You must send 64 color values to the RGB matrix before it displays an image!
char spi_transfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait for the end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}
