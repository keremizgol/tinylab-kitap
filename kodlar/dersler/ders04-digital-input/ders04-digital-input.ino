#define ledPin 12
#define buttonApin 9
#define buttonBpin 8

void setup() 
{
  //LED i cikis, butonlari giris olarak ayarla
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  //A butonuna basilinca LED i yak
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  //B butonuna basilinca LED i sondur
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
}
