//LED baglantilari
#define kirmiziLEDPin 3
#define yesilLEDPin 5
#define maviLEDPin 6
//buton baglantilari
#define kirmiziSwitchPin 9
#define yesilSwitchPin 8
#define maviSwitchPin A5

//varsayilan degerler
int kirmizi = 0;
int mavi = 0;
int yesil = 0;

void setup()
{
  //ledleri cikis, butonları giris olarak ayarla
  pinMode(kirmiziLEDPin, OUTPUT);
  pinMode(yesilLEDPin, OUTPUT);
  pinMode(maviLEDPin, OUTPUT);
  pinMode(kirmiziSwitchPin, INPUT_PULLUP);
  pinMode(yesilSwitchPin, INPUT_PULLUP);
}

void loop()
{
  //kirmizi butonuna basildigi surece degeri birer arttir
  if (digitalRead(kirmiziSwitchPin) == LOW)
  {
    kirmizi ++;
    if (kirmizi > 255) {
      kirmizi = 0;
    }
  }
  //yesil butonuna basildigi surece degeri birer arttir
  if (digitalRead(yesilSwitchPin) == LOW)
  {
    yesil ++;
    if (yesil > 255) {
      yesil = 0;
    }
  }
  //mavi butonuna basildigi surece degeri birer arttir
  if (analogRead(maviSwitchPin) >= 185 && analogRead(maviSwitchPin) <= 225)
  {
    mavi ++;
    if (mavi > 255) {
      mavi = 0;
    }
  }
  //S4 e basildiginda sondur
  if (analogRead(maviSwitchPin) >= 489 && analogRead(maviSwitchPin) <= 529)
  {
    kirmizi = 0;
    yesil = 0;
    mavi = 0;
  }
  renkAyarla(kirmizi, yesil, mavi);
  delay(10);
}

void renkAyarla(int kirmizi, int yesil, int mavi)
{
  //ortak anot icin degerleri tersine cevirmemiz gerekli
  kirmizi = 255 - kirmizi;
  yesil = 255 - yesil;
  mavi = 255 - mavi;
  //analog cikislara parlaklik degerlerini yaz
  analogWrite(kirmiziLEDPin, kirmizi);
  analogWrite(yesilLEDPin, yesil);
  analogWrite(maviLEDPin, mavi);
}

