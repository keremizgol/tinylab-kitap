//gerekli kutuphaneler: 24LC256 icin ExtEEPROM.h, I2C haberlesme icin Wire.h
#include <ExtEEPROM.h>
#include <Wire.h>

//24LC256 I2C adresi
#define hwaddress 0x50

//I2C EEPROM icin tanimlama
ExtEEPROM eeprom(hwaddress);

void setup()
{
  //seri iletisimi 9600 baud'da baslat
  Serial.begin(9600);
  Serial.println("EEPROM okuma ornegi.");
  delay(3000);
  //adres degeri 256 olana kadar EEPROM'dan veri oku
  for (int addr = 0; addr <= 320; addr++)
  {
    //EEPROM'dan addr adresindeki veriyi oku
    int val = eeprom.read(addr);
    //suan okunan EEPROM adres numarasini yaz
    Serial.print(addr);
    //bosluk birak
    Serial.print("\t");
    //EEPROM'dan okunan veriyi ekrana yaz
    Serial.println(val);
    delay(200);
  }
  Serial.print("Hafizanin sonuna gelindi");
}

void loop()
{

}
