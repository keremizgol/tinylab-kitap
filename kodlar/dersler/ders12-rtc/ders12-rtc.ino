//gerekli kutuphaneler: I2C haberlesme icin Wire.h,
//saat fonksiyonlari icin Time.h,
//DS1307 RTC entegresi icin DS1307RTC.h,
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

void setup() 
{
  //seri iletisimi 9600 baud'da baslat
  Serial.begin(9600);
  //seri monitor acilana kadar bekle
  while (!Serial);
  delay(200);
  Serial.println("DS1307RTC Okuma Testi");
  Serial.println("---------------------");
}

void loop() 
{
  //tm formatinda saat bilgisini okumak icin bu satiri ekliyoruz
  tmElements_t tm;

  if (RTC.read(tm)) //RTC entegresinden tm formatinda okunabiliyorsa 
  {
    //saat formati: SS:DD:ss
    Serial.print("Saat = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    //tarih formati: GG/AA/YYYY
    Serial.print(", Tarih (G/A/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
  else //hata mesajlari
  {
    if (RTC.chipPresent()) //RTC okunuyor fakat saat ayarli degilse
    {
      Serial.println("RTC saati ayarli degil.");
      Serial.println("Lutfen once SetTime programi ile saati ayarlayin.");
      Serial.println();
    }
    else //RTC okunamiyorsa
    {
      Serial.println("RTC okuma hatasi.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) //saati iki haneli olarak yaz
{
  if (number >= 0 && number < 10) //saat tek basamakli ise onlar basamagina 0 koy
  {
    Serial.write('0');
  }
  Serial.print(number);
}
