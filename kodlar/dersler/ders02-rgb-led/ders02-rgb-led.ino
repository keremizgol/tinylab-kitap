//pin tanimlamalari
#define kirmiziPin 3
#define yesilPin 5
#define maviPin 6

void setup()
{
  //pinleri cikis olarak ayarla
  pinMode(kirmiziPin, OUTPUT);
  pinMode(yesilPin, OUTPUT);
  pinMode(maviPin, OUTPUT);
}

void loop()
{
  renkAyarla(255, 0, 0); //kirmizi
  delay(1500);
  renkAyarla(0, 255, 0); //yesil
  delay(1500);
  renkAyarla(0, 0, 255); //mavi
  delay(1500);
  renkAyarla(255, 255, 0); //sari
  delay(1500);
  renkAyarla(80, 0, 80); //mor
  delay(1500); 
  renkAyarla(0, 255, 255); //acik mavi
  delay(1500);
  renkAyarla(255, 255, 255); //beyaz
  delay(1500);
}

void renkAyarla(int kirmizi, int yesil, int mavi)
{
  //ortak anot icin degerleri tersine cevirmemiz gerekli
  kirmizi = 255 - kirmizi;
  yesil = 255 - yesil;
  mavi = 255 - mavi;
  //analog cikislara parlaklik degerlerini yaz
  analogWrite(kirmiziPin, kirmizi);
  analogWrite(yesilPin, yesil);
  analogWrite(maviPin, mavi);
}
