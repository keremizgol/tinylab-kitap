//gerekli kutuphaneler: I2C haberlesme icin Wire.h
//saat fonksiyonlari icin Time.h,
//DS1307 RTC entegresi icin DS1307RTC.h,
//gerekli kutuphaneler: MAX7219 7-segment surucu icin LedControl.h
//I2C LCD icin LiquidTWI2.h
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LedControl.h>
#include <LiquidTWI2.h>

//sicaklik sensoru pini
#define LM35_PIN A3

//I2C LCD icin tanimlama
LiquidTWI2 lcd(0x20);
//DataIn, Clock, Load, surucu sayisi
LedControl lc = LedControl(10, 12, 11, 1);

//delay kullanmadan bekleme fonksiyonu icin degiskenler
bool state = LOW;
int previousMillis = 0;
int interval = 2500;

//7-segment gosterge icin degiskenler
int temp = 0;
int temp_first_digit = 0;
int temp_second_digit = 0;
int hour_first_digit = 0;
int hour_second_digit = 0;
int minute_first_digit = 0;
int minute_second_digit = 0;

void setup()
{
  //gostergeyi calistir
  lc.shutdown(0, false);
  //gosterge parlakligini 0-15 arasinda ayarla
  lc.setIntensity(0, 8);
  //gostergeyi temizle
  lc.clearDisplay(0);
  //I2C LCD icin ayar
  lcd.setMCPType(LTI_TYPE_MCP23008);
  //16 sutun, 2 satir
  lcd.begin(16, 2);
  //arka isigi ac
  lcd.setBacklight(HIGH);
  delay(300);
}

void loop()
{
  //suanki zamani hafizada tut
  int currentMillis = millis();
  //lm35 i oku ve degeri santigrada cevir
  temp = (5.0 * analogRead(LM35_PIN) * 100.0) / 1024;
  //lcd ekrana tarih ve saati yaz
  lcd_print();
  //suanki zaman ile bir onceki zamanin farki bekleme suresi kadar ise
  if (currentMillis - previousMillis > interval) 
  {
    //zaman bilgisini sifirla
    previousMillis = currentMillis;
    //state degiskeni 0 ise
    if (state == LOW)
    {
      //7-segment gostergeye saati yaz
      led_clock();
      //state degiskenini 1 yap
      state = HIGH;
    }
    //state degiskeni 0 degil ise
    else
    {
      //7-segment gostergeye sicaklik bilgisini yaz
      led_temp();
      //state degiskenini 0 yap
      state = LOW;
    }
  }
  
}

//7-segment gostergeye saati yazma fonksiyonu
void led_clock()
{
  //tm formatinda saat bilgisini okumak icin bu satiri ekliyoruz
  tmElements_t tm;
  if (RTC.read(tm))//RTC entegresinden tm formatinda okunabiliyorsa 
  {
    //saat degerini basamaklarina ayir
    convertTwoDigits(tm.Hour, &hour_first_digit, &hour_second_digit);
    //7-segment gostergeye saati basamak basamak yaz
    lc.setDigit(0, 0, hour_first_digit, false);
    lc.setDigit(0, 1, hour_second_digit, true);
    //dakika degerini basamaklarina ayir
    convertTwoDigits(tm.Minute, &minute_first_digit, &minute_second_digit);
    //7-segment gostergeye dakikayi basamak basamak yaz
    lc.setDigit(0, 2, minute_first_digit, false);
    lc.setDigit(0, 3, minute_second_digit, false);
  }
  else //RTC entegresi okunamiyorsa tum hanelere 8 yaz
  {
    lc.setDigit(0, 0, 8, true);
    lc.setDigit(0, 1, 8, true);
    lc.setDigit(0, 2, 8, true);
    lc.setDigit(0, 3, 8, true);
  }
}

//7-segment gostergeye sicaklik yazma fonksiyonu
void led_temp()
{
  //sicaklik degerini basamaklarina ayir
  convertTwoDigits(temp, &temp_first_digit, &temp_second_digit);
  //7-segment gostergenin ilk iki hanesine sicakligi basamak basamak yaz
  lc.setDigit(0, 0, temp_first_digit, false);
  lc.setDigit(0, 1, temp_second_digit, false);
  //7-segment gostergenin son iki hanesine santigrad derece sembolu yaz
  lc.setRow(0, 2, B01100011); //derece sembolu
  lc.setRow(0, 3, B01001110); //C harfi
}

//iki basamakli sayiyi basamaklarina ayirma fonksiyonu
void convertTwoDigits(int number, int *first, int *second ) {
  //sayi 10'dan kucukse tek basamaklidir, ilk haneyi 0 yap
  if (number >= 0 && number < 10)
  {
    *first = 0;
    *second = number;
  }
  //sayi 10'dan buyukse
  else
  {
    //onlar basamagini sayinin 1/10'una esitle
    *first = number / 10;
    //birler basamagini sayinin 10'dan bolumune kalanina esitle
    *second = number % 10;
  }
}

//RTC entegresini okuma fonksiyonu
void rtc_read()
{
  //tm formatinda saat bilgisini okumak icin bu satiri ekliyoruz
  tmElements_t tm;
  //RTC entegresi okunamiyorsa ekrana hata mesaji yaz
  if (RTC.chipPresent())
    lcd.print("RTC Okuma Hatasi!");
}

//LCD ekrana tarih ve saat yazma fonksiyonu
//GG.AA.YYYY
//SS:DD:ss
void lcd_print()
{
  //tm formatinda saat bilgisini okumak icin bu satiri ekliyoruz
  tmElements_t tm;
  //RTC entegresinden tm formatinda okunabiliyorsa 
  if (RTC.read(tm))
  {
    //imleci ekranin birinci satir dorduncu sutuna getir
    lcd.setCursor(3, 0);
    if (tm.Day < 10) //gun tek haneliyse basina 0 koy
      lcd.print("0");
    //gun bilgisini yaz
    lcd.print(tm.Day);
    //gun ile ay ayiraci koy
    lcd.print(".");
    if (tm.Month < 10) //ay tek haneliyse basina 0 koy
      lcd.print("0");
    //ay bilgisini yaz
    lcd.print(tm.Month);
    //ay ile yil ayiraci koy
    lcd.print(".");
    //yili dort haneli olarak yaz
    lcd.print(tmYearToCalendar(tm.Year));
    //imleci ikinci satir besinci sutuna getir
    lcd.setCursor(4, 1);
    if (tm.Hour < 10) //saat tek haneliyse basina 0 koy
      lcd.print("0");
    //saat bilgisini yaz
    lcd.print(tm.Hour);
    //saat ile dakika ayiraci koy
    lcd.print(":");
    if (tm.Minute < 10) //dakika tek haneliyse basina 0 koy
      lcd.print("0");
    //dakika bilgisini yaz
    lcd.print(tm.Minute);
    //dakika ile saniye ayiraci koy
    lcd.print(":");
    if (tm.Second < 10) //saniye tek haneliyse basina 0 koy
      lcd.print("0");
    //saniye bilgisini yaz
    lcd.print(tm.Second);
  }
  else //RTC okunamiyorsa ekrana hata mesaji yaz
  {
    if (RTC.chipPresent())
    {
      lcd.setCursor(0, 0);
      lcd.print("RTC Okuma Hatasi");
    }
  }
}

