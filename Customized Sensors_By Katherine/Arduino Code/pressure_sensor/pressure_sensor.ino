int IRledPin = 12;
int IRrecPin1 = 0;
int IRrecPin2 = 1;
int value1;
int value2;
int counter;

void setup()
{
  Serial.begin(9600);
  pinMode(IRledPin, OUTPUT);
  digitalWrite(IRledPin, HIGH);
  pinMode(IRrecPin1, INPUT);
  pinMode(IRrecPin2, INPUT);
}

void loop()
{
  value1 = analogRead(IRrecPin1);
  value2 = analogRead(IRrecPin2);
  delay(5);
  Serial.write(value1 >> 2);
  delay(90);
}
