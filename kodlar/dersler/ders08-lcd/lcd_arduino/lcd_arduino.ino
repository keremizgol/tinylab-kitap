//gerekli kutuphaneler: LCD icin LiquidCrystal.h
#include <LiquidCrystal.h>

//sensor pinleri
#define lm35_pin A3
#define ldr_pin A2

//LCD ekran pinleri sirasiyla RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  //16 sutun, 2 satir
  lcd.begin(16, 2);
  //ilk satıra LCD Demo yaz
  lcd.print("LCD Demo");
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
