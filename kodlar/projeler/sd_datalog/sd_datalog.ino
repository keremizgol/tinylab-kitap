#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
const int LM35_pin = A3;
float temp = 0;

void setup()
{
  pinMode(LM35_pin, INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("SD karta erisiliyor...");

  if (!SD.begin(chipSelect))
  {
    Serial.println("Kart hatasi.");
    return;
  }
  Serial.println("Erisim basarili.");
  delay(3000);
}

void loop()
{
  String dataString = "";
  int temp = (5.0 * analogRead(LM35_pin) * 100.0) / 1024;
  dataString += String(temp);

  File dataFile = SD.open("temp.txt", FILE_WRITE);

  if (dataFile)
  {
    dataFile.print("Sicaklik: ");
    dataFile.println(dataString); 
    dataFile.close();
    Serial.print("Sicaklik: ");
    Serial.println(dataString);
  }
  else
    Serial.println("temp.txt dosyasina yazilamadi.");
}
