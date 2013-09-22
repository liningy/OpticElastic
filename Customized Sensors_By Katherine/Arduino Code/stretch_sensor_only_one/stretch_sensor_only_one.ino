int IRrecPin1 = 0;
int value1;
int nostretch1;
int yesstretch1;
int fraction1;

boolean visualization = true;

void setup()
{
  Serial.begin(9600);
  pinMode(IRrecPin1, INPUT);
  
  nostretch1 = 1024;
  yesstretch1 = 0;
  
  int start_time = millis();
  while (millis() - start_time < 1000) {
    value1 = analogRead(IRrecPin1);
    nostretch1 = min(nostretch1, value1);
    delay(50);
  }
  
  start_time = millis();
  while (millis() - start_time < 5000) {
    value1 = analogRead(IRrecPin1);
    yesstretch1 = max(yesstretch1, value1);
    delay(50);
  }
  if (!visualization) {
    Serial.print("min 1: ");
    Serial.print(nostretch1);
    Serial.print(" max 1: ");
    Serial.println(yesstretch1);
  }
  delay(1000);
}

void loop()
{
  value1 = analogRead(IRrecPin1);

  fraction1 = (int) (100.0 * (double)(value1-nostretch1) / (double)(yesstretch1 - nostretch1));
  fraction1 = 100 - constrain(fraction1, 0, 100);
  
  if (!visualization) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(value1);
    Serial.print(" ");
    Serial.println(fraction1);
  }
  else {    
    Serial.write(fraction1);
  }
  delay(90);
}
