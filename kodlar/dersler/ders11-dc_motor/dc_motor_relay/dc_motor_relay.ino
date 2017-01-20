//buton ve role pinleri
#define relayPin A4
#define buttonApin 9
#define buttonBpin 8

void setup() 
{
  //role pinini cikis, butonlari giris olarak ayarla
  pinMode(relayPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  //A butonuna basilinca roleyi iletime sok
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(relayPin, HIGH);
  }
  //B butonuna basilinca roleyi kesime sok
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(relayPin, LOW);
  }
}
