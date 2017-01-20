//gerekli kutuphaneler: MAX7219 7-segment surucu icin LedControl.h
#include <LedControl.h>

//potansiyometre ve motor surucu pin tanimlamalari
#define pot_pin A0
#define motor_pin 5

//DataIn, Clock, Load, surucu sayisi
LedControl lc = LedControl(10, 12, 11, 1);

//baslangic degerleri
int motor_spd = 0;
int percent = 0;

void setup()
{
  //motor surucunun yer aldigi pini cikis olarak ayarla
  pinMode(motor_pin, OUTPUT);
  //gostergeyi calistir
  lc.shutdown(0, false);
  //gosterge parlakligini 0-15 arasinda ayarla
  lc.setIntensity(0, 8);
  //gostergeyi temizle
  lc.clearDisplay(0);
}

void loop()
{
  //potanstan gelen 0-1023 arasi degeri PWM cikis isin 0-255 arasinda olcekle
  motor_spd = analogRead(pot_pin) / 4;
  //motor surucu pininden PWM cikis ver
  analogWrite(motor_pin, motor_spd);
  //0-255 arasi PWM degerini yuzde olarak olcekle
  int percent = map(motor_spd, 0, 255, 0, 100);
  //motor calisma hizini yuzde olarak 7-segment'e yaz
  printToDisplay(percent);
  //20ms bekle
  delay(20);
}

//7-segment gostergeye deger yazmak icin gerekli fonksiyon
void printToDisplay(int value)
{
  //pozitif sayilari yazma metodu
  if (value >= 0)
  {
    //bir basamakli sayilar
    if (value < 10)
    {
      //birler basamagina sayinin 10 ile bolumunden kalanı yaz
      lc.setDigit(0, 3, (value % 10), false);
      //diger basamaklari bos birak
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    //iki basamakli sayilar
    if (value >= 10 && value < 99)
    {
      //birler basamagina sayinin 10 ile bolumunden kalani yaz
      lc.setDigit(0, 3, (value % 10), false);
      //sayiyi 10'a bol, sonucun 10 ile bolumunden kalani onlar basamagina yaz
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      //diger basamaklari bos birak
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    //uc basamakli sayilar
    if (value > 100 && value <= 999)
    {
      //birler basamagina sayinin 10 ile bolumunden kalani yaz
      lc.setDigit(0, 3, (value % 10), false);
      //sayiyi 10'a bol, sonucun 10 ile bolumunden kalani onlar basamagina yaz
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      //sayiyi 100'e bol, sonucun 10 ile bolumunden kalani yuzler basamagina yaz
      lc.setDigit(0, 1, ((value / 100) % 10), false);
      //diger basamaklari bos birak
      lc.setRow(0, 0, B00000000);
    }
    //dort basamakli sayilar
    if (value >= 1000)
    {
      //birler basamagina sayinin 10 ile bolumunden kalani yaz
      lc.setDigit(0, 3, (value % 10), false);
      //sayiyi 10'a bol, sonucun 10 ile bolumunden kalani onlar basamagina yaz
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      //sayiyi 100'e bol, sonucun 10 ile bolumunden kalani yuzler basamagina yaz
      lc.setDigit(0, 1, ((value / 100) % 10), false);
      //sayiyi 1000'e bol, sonucun 10 ile bolumunden kalani binler basamagina yaz
      lc.setDigit(0, 0, ((value / 1000) % 10), false);
    }
  }
  //negatif sayilari yazma metodu
  if (value < 0)
  {
    //bir basamakli sayilar
    if (value >= -10)
    {
      //sayinin mutlak degerinin 10'a bolumunden kalanini birler basamagina yaz
      lc.setDigit(0, 3, (abs(value) % 10), false);
      //bir sonraki basamaga eksi isareti koy
      lc.setRow(0, 2, B00000001);
      //diger basamaklari bos birak
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    //iki basamakli sayilar
    if (value >= -100 && value <= -10)
    {
      //sayinin mutlak degerinin 10'a bolumunden kalanini birler basamagina yaz
      lc.setDigit(0, 3, (abs(value) % 10), false);
      //sayinin mutlak degerini 10'a bol, sonucun 10'a bolumunden kalani onlar basamagina yaz
      lc.setDigit(0, 2, ((abs(value) / 10) % 10), false);
      //bir sonraki basamaga eksi isareti koy
      lc.setRow(0, 1, B00000001);
      //diger basamaklari bos birak
      lc.setRow(0, 0, B00000000);
    }
    //uc basamakli sayilar
    if (value >= -1000 && value <= -100)
    {
      //sayinin mutlak degerinin 10'a bolumunden kalanini birler basamagina yaz
      lc.setDigit(0, 3, (abs(value) % 10), false);
      //sayinin mutlak degerini 10'a bol, sonucun 10'a bolumunden kalani onlar basamagina yaz
      lc.setDigit(0, 2, ((abs(value) / 10) % 10), false);
      //sayinin mutlak degerini 100'e bol, sonucun 10'a bolumunden kalani yuzler basamagina yaz
      lc.setDigit(0, 1, ((abs(value) / 100) % 10), false);
      //bir sonraki basamaga eksi isareti koy
      lc.setRow(0, 0, B00000001);
    }
  }
}
