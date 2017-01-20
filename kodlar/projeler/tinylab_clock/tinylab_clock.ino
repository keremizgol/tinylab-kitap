#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LedControl.h>
#include <LiquidTWI2.h>

#define LM35_PIN A3

LedControl lc = LedControl(10, 12, 11, 1);
LiquidTWI2 lcd(0x20);

uint32_t timer = 0;
int temp = 0;
unsigned long delaytime = 250;
int hour_first_digit = 0;
int hour_second_digit = 0;
int minute_first_digit = 0;
int minute_second_digit = 0;
int temp_first_digit = 0;
int temp_second_digit = 0;

void setup()
{
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 6);
  lc.clearDisplay(0);

  lcd.setMCPType(LTI_TYPE_MCP23008);
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);

  delay(300);
}

void convertTwoDigits(int number, int *first, int *second ) {
  if (number >= 0 && number < 10)
  {
    *first = 0;
    *second = number;
  }
  else
  {
    *first = number / 10;
    *second = number % 10;
  }
}

void loop()
{
  tmElements_t tm;

  temp = (5.0 * analogRead(LM35_PIN) * 100.0) / 1024;

  if (millis() - timer < 2000)
  {
    if (RTC.read(tm))
    {
      convertTwoDigits(tm.Hour, &hour_first_digit, &hour_second_digit);
      lc.setDigit(0, 0, hour_first_digit, false);
      lc.setDigit(0, 1, hour_second_digit, true);
      convertTwoDigits(tm.Minute, &minute_first_digit, &minute_second_digit);
      lc.setDigit(0, 2, minute_first_digit, false);
      lc.setDigit(0, 3, minute_second_digit, false);
    }
    else
    {
      if (RTC.chipPresent())
      {
        Serial.println("The DS1307 is stopped.  Please run the SetTime");
        Serial.println("example to initialize the time and begin running.");
        Serial.println();
      }
      else
      {
        Serial.println("DS1307 read error!  Please check the circuitry.");
        Serial.println();
      }
    }
  }
  else
  {
    lc.clearDisplay(0);
    convertTwoDigits(temp, &temp_first_digit, &temp_second_digit);
    lc.setDigit(0, 0, temp_first_digit, false);
    lc.setDigit(0, 1, temp_second_digit, false);
    lc.setRow(0, 2, B01100011);
    lc.setRow(0, 3, B01001110);

    delay(2000);
    timer = millis();
  }

  lcd.setCursor(3, 0);
  if (tm.Day < 10)
    lcd.print("0");
  lcd.print(tm.Day);
  lcd.print(".");
  if (tm.Month < 10)
    lcd.print("0");
  lcd.print(tm.Month);
  lcd.print(".");
  lcd.print(tmYearToCalendar(tm.Year));

  lcd.setCursor(4, 1);
  if (tm.Hour < 10)
    lcd.print("0");
  lcd.print(tm.Hour);
  lcd.print(":");
  if (tm.Minute < 10)
    lcd.print("0");
  lcd.print(tm.Minute);
  lcd.print(":");
  if (tm.Second < 10)
    lcd.print("0");
  lcd.print(tm.Second);
}



