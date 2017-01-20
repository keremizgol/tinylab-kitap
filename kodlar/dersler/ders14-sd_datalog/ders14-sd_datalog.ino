//gerekli kutuphaneler: SPI haberlesme icin SPI.h,
//SD kart icin SD.h,
//I2C haberlesme icin Wire.h,
//saat fonksiyonlari icin Time.h,
//DS1307 RTC entegresi icin DS1307RTC.h,
//I2C LCD icin LiquidTWI2.h
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidTWI2.h>

//SD kartin chip select (CS) pini ve sicaklik sensoru pin tanimlamalari
#define chipSelect 4
#define LM35_pin A3

//I2C LCD icin tanimlama
LiquidTWI2 lcd(0);

//sicaklik icin baslangic degeri
float temp = 0;

void setup()
{
  //I2C LCD icin ayarlar
  lcd.setMCPType(LTI_TYPE_MCP23008);
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.print("Karta erisiliyor");
  //kart mevcut degilse veya erisilemiyorsa LCD'ye hata mesaji yaz
  if (!SD.begin(chipSelect))
  {
    lcd.setCursor(0, 1);
    lcd.print("Kart hatasi");
    return;
  }
  delay(2500);
  //karta erisim mevcutsa LCD'ye mesaj yaz, daha sonra LCD'yi kapat
  lcd.setCursor(0, 1);
  lcd.print("Erisim basarili");
  delay(3000);
  lcd.setBacklight(LOW);
  lcd.clear();
}

void loop()
{
  //tm formatinda saat bilgisini okumak icin bu satiri ekliyoruz
  tmElements_t tm;
  //SD karta yazilacak veriyi bir string'de tutmamiz gerekli
  String dataString = "";
  //lm35 i oku ve degeri santigrada cevir
  temp = (5.0 * analogRead(LM35_pin) * 100.0) / 1024;
  //string'e sicaklik degerini ekle
  dataString += String(temp);

  //RTC'den saat bilgisi alinabiliyorsa
  if (RTC.read(tm))
  {
    //SD kartta datalog.txt isimli bir dosya olustur
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    //dosyaya yazilabiliyorsa
    if (dataFile)
    {
      //saat ve tarih bilgisini dosyaya yaz
      //GG//AA/YYYY, SS:DD:ss
      if (tm.Day < 10)
        dataFile.print("0");
      dataFile.print(tm.Day);
      dataFile.print("/");
      if (tm.Month < 10)
        dataFile.print("0");
      dataFile.print(tm.Month);
      dataFile.print("/");
      dataFile.print(tmYearToCalendar(tm.Year));
      dataFile.print(",");
      if (tm.Hour < 10)
        dataFile.print("0");
      dataFile.print(tm.Hour);
      dataFile.print(":");
      if (tm.Minute < 10)
        dataFile.print("0");
      dataFile.print(tm.Minute);
      dataFile.print(":");
      if (tm.Second < 10)
        dataFile.print("0");
      dataFile.print(tm.Second);
      //saat ve tarihten sonra sicaklik degerini ekle
      dataFile.print(" Sicaklik: ");
      dataFile.print(dataString);
      dataFile.println(" °C");
      //yazma islemini bitir
      dataFile.close();
    }
    //dosyaya yazilamiyorsa LCD'de hata mesaji goster
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Dosya yazilamadi");
    }
  }
  delay(1000);
}
