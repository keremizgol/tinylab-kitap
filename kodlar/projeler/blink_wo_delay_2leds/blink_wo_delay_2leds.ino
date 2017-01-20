//LED'lerin bagli oldugu pinler
#define led1Pin 13
#define led2Pin 12

//baslangic degerleri ve bekleme sureleri
bool led1Durum = LOW;
bool led2Durum = LOW;
unsigned long oncekiZaman1 = 0;
unsigned long oncekiZaman2 = 0;
const long aralik1 = 500;
const long aralik2 = 300;

void setup()
{
  //LED pinlerini cikis olarak ayarla
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop()
{
  //suanki zamani hafizada tut
  unsigned long simdikiZaman = millis();

  //suanki zaman ile bir onceki zamanin farki birinci LED'in bekleme suresi kadar ise
  if(simdikiZaman - oncekiZaman1 >= aralik1)
  {
    //zaman bilgisini sifirla
    oncekiZaman1 = simdikiZaman;
    //led1Durum'u tersine cevir
    led1Durum = !led1Durum;
  }

  //suanki zaman ile bir onceki zamanin farki ikinci LED'in bekleme suresi kadar ise
  if(simdikiZaman - oncekiZaman2 >= aralik2)
  {
    //zaman bilgisini sifirla
    oncekiZaman2 = simdikiZaman;
    //led2Durum'u tersine cevir
    led2Durum = !led2Durum;
  }
  //LED durum degiskenlerini LED'lere yaz
  digitalWrite(led1Pin, led1Durum);
  digitalWrite(led2Pin, led2Durum);
}

