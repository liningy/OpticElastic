int IRrecPin1 = 0;
int IRrecPin2 = 1;
int value1;
int value2;
int nostretch1;
int yesstretch1;
int nostretch2;
int yesstretch2;
double latesttouch1 = 0;
double latesttouch2 = 0;
double latestswipe = 0;
int fraction1;
int fraction2;
int avgfraction;

boolean visualization = true;

void setup()
{
  Serial.begin(9600);
  pinMode(IRrecPin1, INPUT);
  pinMode(IRrecPin2, INPUT);
  
  nostretch1 = 0;
  yesstretch1 = 1024;
  nostretch2 = 0;
  yesstretch2 = 1024;
  
  int start_time = millis();
  while (millis() - start_time < 1000) {
    value1 = analogRead(IRrecPin1);
    value2 = analogRead(IRrecPin2);
    nostretch1 = max(nostretch1, value1);
    nostretch2 = max(nostretch2, value2);
    delay(50);
  }
  
  start_time = millis();
  while (millis() - start_time < 5000) {
    value1 = analogRead(IRrecPin1);
    value2 = analogRead(IRrecPin2);
    yesstretch1 = min(yesstretch1, value1);
    yesstretch2 = min(yesstretch2, value2);
    delay(50);
  }
  if (!visualization) {
    Serial.print("max 1: ");
    Serial.print(nostretch1);
    Serial.print(" min 1: ");
    Serial.print(yesstretch1);
    Serial.print(" max 2: ");
    Serial.print(nostretch2);
    Serial.print(" min 2: ");
    Serial.println(yesstretch2);
  }
  delay(1000);
}

void loop()
{
  value1 = analogRead(IRrecPin1);
  value2 = analogRead(IRrecPin2);

  fraction1 = (int) (100.0 * (double)(value1-yesstretch1) / (double)(nostretch1 - yesstretch1));
  fraction2 = (int) (100.0 * (double)(value2-yesstretch2) / (double)(nostretch2 - yesstretch2));
  avgfraction = (fraction1 + fraction2) / 2;
  avgfraction = constrain(avgfraction, 0, 100);
  
  if (!visualization) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(value1);
    Serial.print(" ");
    Serial.print(value2);
    Serial.print(" ");
    Serial.println(avgfraction);
  }
  else {    
    Serial.write(avgfraction);
  }
  delay(90);
}
