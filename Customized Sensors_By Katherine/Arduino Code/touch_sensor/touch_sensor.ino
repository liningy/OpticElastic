int IRledPin = 12;
int IRrecPin1 = 0;
int IRrecPin2 = 1;
int value1;
int value2;
int notouch1;
int yestouch1;
int notouch2;
int yestouch2;
double latesttouch1 = 0;
double latesttouch2 = 0;
double latestswipe = 0;
int fraction1;
int fraction2;
boolean left;
boolean right;

boolean visualization = true;

void setup()
{
  Serial.begin(9600);
  pinMode(IRledPin, OUTPUT);
  digitalWrite(IRledPin, HIGH);
  pinMode(IRrecPin1, INPUT);
  pinMode(IRrecPin2, INPUT);
  
  notouch1 = 1024;
  yestouch1 = 0;
  notouch2 = 1024;
  yestouch2 = 0;
  
  int start_time = millis();
  while (millis() - start_time < 1000) {
    value1 = analogRead(IRrecPin1);
    value2 = analogRead(IRrecPin2);
    notouch1 = min(notouch1, value1);
    notouch2 = min(notouch2, value2);
    delay(50);
  }
  
  start_time = millis();
  while (millis() - start_time < 5000) {
    value1 = analogRead(IRrecPin1);
    value2 = analogRead(IRrecPin2);
    yestouch1 = max(yestouch1, value1);
    yestouch2 = max(yestouch2, value2);
    delay(50);
  }
  if (!visualization) {
    Serial.print("min 1: ");
    Serial.print(notouch1);
    Serial.print(" max 1: ");
    Serial.print(yestouch1);
    Serial.print(" min 2: ");
    Serial.print(notouch2);
    Serial.print(" max 2: ");
    Serial.println(yestouch2);
  }
  delay(1000);
}

void loop()
{
  value1 = analogRead(IRrecPin1);
  value2 = analogRead(IRrecPin2);
  left = false;
  right = false;
  
  fraction1 = (100 * (value1-notouch1)) / (yestouch1-notouch1);
  fraction2 = (100 * (value2-notouch2)) / (yestouch2-notouch2);
  fraction1 = constrain(fraction1,0,100);
  fraction2 = constrain(fraction2,0,100);
  if (fraction1 > 50) {
    latesttouch1 = millis();
  }
  if (fraction2 > 50) {
    latesttouch2 = millis();
  }
  
  if (latestswipe < millis() - 250 && fraction2 > 50 && latesttouch1 > millis() - 500 && fraction1 < 20) {
    left = true;
    latestswipe = millis();
  }
  if (latestswipe < millis() - 250 && fraction1 > 50 && latesttouch2 > millis() - 500 && fraction2 < 20) {
    right = true;
    latestswipe = millis();
  }
  
  if (!visualization) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(value1);
    Serial.print(" ");
    Serial.print(fraction1);
    Serial.print(" ");
    Serial.print(value2);
    Serial.print(" ");
    Serial.println(fraction2);
    
    if (left) {
      Serial.println("left!");
    }
    if (right) {
      Serial.println("right!");
    }
  }
  else {    
    Serial.write(255);
    delay(2);
    Serial.write(fraction1);
    delay(2);
    Serial.write(fraction2);
    delay(2);
    if (left) {
      Serial.write(1);
    }
    else if (right) {
      Serial.write(2);
    }
    else {
      Serial.write(0);
    }
  }
  delay(90);
}
