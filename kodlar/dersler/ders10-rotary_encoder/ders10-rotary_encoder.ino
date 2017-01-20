//enkoder baglanti pinleri
#define pinA 6
#define pinB 7

//baslangic degerleri
int encoderPos = 0;
bool pinALast = LOW;
bool n = LOW;

void setup() 
{
  //enkoder pinlerini giris olarak ayarla, pull-up direnclerini aktiflestir
  pinMode (pinA, INPUT_PULLUP);
  pinMode (pinB, INPUT_PULLUP);
  //seri haberlesmeyi 9600 baud'da baslat
  Serial.begin (9600);
}

void loop()
{
  //enkoderin A pinini oku
  n = digitalRead(pinA);
  //A pini 0 dan 1 e gectiyse
  if ((pinALast == LOW) && (n == HIGH)) 
  {
    if (digitalRead(pinB) == LOW) //B pini 0 daysa
      encoderPos++; //enkoder degerini arttir
    else
      encoderPos--; //eknoder degerini azalt
    //enkoder degerini seri porta aktar
    Serial.print("Enkoder konumu: ");  
    Serial.println(encoderPos);
  }
  pinALast = n; //A pininin en son durumunu n'e esitle
  //S4 e basildiginda enkoder degerini sifirla
  if (analogRead(A5) >= 80 && analogRead(A5) <= 100) 
  {
    encoderPos = 0;
    Serial.println("Enkoder sifirlandi!");
  }
}
