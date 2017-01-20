//gerekli kutuphaneler: 24LC256 icin ExtEEPROM.h, I2C haberlesme icin Wire.h
#include <ExtEEPROM.h>
#include <Wire.h>

//24LC256 I2C adresi
#define hwaddress 0x50

//I2C EEPROM icin tanimlama
ExtEEPROM eeprom(hwaddress);

void setup()
{
  Serial.begin(9600);
  Serial.println("EEPROM yazma ornegi.");
  delay(3000);
  //adres degeri 256 olana kadar EEPROM'a sicaklik degerlerini yaz
  for (int addr = 0; addr <= 256; addr++)
  {
    //lm35 i oku ve degeri santigrada cevir
    int val = (5.0 * analogRead(A3) * 100.0) / 1024;
    //degeri EEPROM'un addr ile belirtilen byte'ina yaz
    eeprom.write(addr, val);
    //suan okunan EEPROM adres numarasini yaz
    Serial.print(addr);
    //bosluk birak
    Serial.print("\t");
    //EEPROM'a yazilan sicaklik degerini ekrana yaz
    Serial.println(val);
    delay(200);
  }
  Serial.print("Hafiza sonuna gelindi.");
}


void loop()
{

}
