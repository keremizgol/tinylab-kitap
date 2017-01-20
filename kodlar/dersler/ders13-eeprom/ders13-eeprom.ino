#include <ExtEEPROM.h>

#define hwaddress 0x50

ExtEEPROM eeprom(hwaddress);

int addr = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("EEPROM example.");
  delay(3000);
}

void loop()
{
  while (!Serial)
  {
    //read code
    /*
    for (int i = 0; i <= 256 ; i++)
    {
      byte value = eeprom.read(addr);
      Serial.print(addr);
      Serial.print("\t");
      Serial.println(value, DEC);
      addr = addr + 1;
      delay(500);
    }
    Serial.print("End of memory.");
    */

    //write code
    /*
    for (int i = 0; i <= 256; i++)
    {
      int val = (5.0 * analogRead(A3) * 100.0) / 1024;
      eeprom.write(i, val);
      Serial.print(i);
      Serial.print("\t");
      Serial.println(val);
      delay(100);
    }
    Serial.print("End of memory.");
    */
  }
}
