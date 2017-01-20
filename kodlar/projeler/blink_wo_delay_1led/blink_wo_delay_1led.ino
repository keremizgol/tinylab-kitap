//LED'in bagli oldugu pin
#define ledPin 13

//baslangic degerleri ve bekleme suresi
bool ledDurum = LOW;
unsigned long oncekiZaman = 0;
const long aralik = 1000;

void setup()
{
  //LED pinini cikis olarak ayarla
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //suanki zamani hafizada tut
  unsigned long simdikiZaman = millis();

  //suanki zaman ile bir onceki zamanin farki bekleme suresi kadar ise
  if (simdikiZaman - oncekiZaman >= aralik)
  {
    //zaman bilgisini sifirla
    oncekiZaman = simdikiZaman;
    //ledDurum'u tersine cevir
    ledDurum = !ledDurum;
  }
  //ledDurum degiskenini ledPin'e yaz
  digitalWrite(ledPin, ledDurum);
}

