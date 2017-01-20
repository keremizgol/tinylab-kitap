//gerekli kutuphaneler: I2C icin Wire.h,
//I2C LCD icin LiquidTWI2.h
#include <Wire.h>
#include <LiquidTWI2.h>

//sensor pinleri
#define lm35_pin A3
#define ldr_pin A2

//I2C LCD icin tanimlama
LiquidTWI2 lcd(0);

void setup()
{
  //I2C LCD icin ayar
  lcd.setMCPType(LTI_TYPE_MCP23008);
  //16 sutun, 2 satir
  lcd.begin(16, 2);
  //arka isigi ac
  lcd.setBacklight(HIGH);
  //ilk satıra Tinylab LCD Demo yaz
  lcd.print("Tinylab LCD Demo");
  delay(1000);
}

void loop()
{
  //ldr yi oku ve degeri lux e cevir
  int ldr_val = ((2500.0 / (analogRead(ldr_pin) * (5.0 / 1024.0))) - 500) / 10.0;
  //lm35 i oku ve degeri santigrada cevir
  int lm35_val = (5.0 * analogRead(lm35_pin) * 100.0) / 1024;
  //imleci ikinci satir birinci karaktere getir
  lcd.setCursor(0, 1);
  //sicaklik degeri
  lcd.print(lm35_val);
  //derece sembolunu
  lcd.print("\337C");
  //imleci ikinci satir altinci karaktere getir
  lcd.setCursor(5, 1);
  lcd.print("Isik:");
  //isik degeri
  lcd.print(ldr_val);
  lcd.print(" ");
  delay(250);
}
