int buzzerPin = A1;
int LDRPin = A2;

void setup()
{
}

void loop()
{
  int deger = analogRead(LDRPin);
  int pitch = 200 + deger / 4;
  tone(buzzerPin, pitch);
}
