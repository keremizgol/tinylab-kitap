//gerekli kutuphaneler: MAX7219 7-segment surucu icin LedControl.h
#include <LedControl.h>
//sicaklik sensoru lm35 A3'e bagli
#define lm35_pin A3

//DataIn, Clock, Load, surucu sayisi
LedControl lc = LedControl(10, 12, 11, 1);

//baslangic degerleri
int temp = 0;
int temp_first_digit = 0;
int temp_second_digit = 0;

void setup()
{
  //gostergeyi calistir
  lc.shutdown(0, false);
  //gosterge parlakligini 0-15 arasinda ayarla
  lc.setIntensity(0, 8);
  //gostergeyi temizle
  lc.clearDisplay(0);
}

void loop()
{
  //lm35 i oku ve degeri santigrada cevir
  temp = (5.0 * analogRead(lm35_pin) * 100.0) / 1024;
  //gostergeye "tiny" yaz
  lc.setRow(0, 0, B00001111);
  lc.setRow(0, 1, B00000110);
  lc.setRow(0, 2, B01110110);
  lc.setRow(0, 3, B00111011);
  delay(1000);
  //bir sonraki islemden once gostergeyi temizle
  lc.clearDisplay(0);
  //gostergeye "lab" yaz
  lc.setRow(0, 0, B00001110);
  lc.setRow(0, 1, B01111101);
  lc.setRow(0, 2, B00011111);
  delay(1000);
  //bir sonraki islemden once gostergeyi temizle
  lc.clearDisplay(0);
  //gostergeye sicaklik degerini yaz
  if (temp <= 10) //sicaklik tek basamakli ise
  {
    temp_first_digit = temp; //birler basamagina sicakligi
    temp_second_digit = 0; //onlar basamagina 0 yaz
  }
  //birler basamagini hesapla
  temp_first_digit = temp / 10; 
  //onlar basamagini hesapla
  temp_second_digit = temp % 10; 
  //birler basamagini gostergeye yaz
  lc.setDigit(0, 0, temp_first_digit, false); 
  //onlar basamagini gostergeye yaz
  lc.setDigit(0, 1, temp_second_digit, false);
  //gostergeye santigrad derece sembolunu yaz
  lc.setRow(0, 2, B01100011);
  lc.setRow(0, 3, B01001110);
  delay(1000);
}
