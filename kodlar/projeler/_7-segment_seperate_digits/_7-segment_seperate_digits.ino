#include "LedControl.h"

LedControl lc = LedControl(10, 12, 11, 1);

const int delay_time = 1000;

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop()
{
  printToDisplay(millis() / 1000);
}

void printToDisplay(int value)
{
  //pozitif
  if (value >= 0)
  {
    if (value < 10)
    {
      lc.setDigit(0, 3, (value % 10), false);
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    if (value >= 10 && value < 99)
    {
      lc.setDigit(0, 3, (value % 10), false);
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    if (value > 100 && value <= 999)
    {
      lc.setDigit(0, 3, (value % 10), false);
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      lc.setDigit(0, 1, ((value / 100) % 10), false);
      lc.setRow(0, 0, B00000000);
    }
    if (value >= 1000)
    {
      lc.setDigit(0, 3, (value % 10), false);
      lc.setDigit(0, 2, ((value / 10) % 10), false);
      lc.setDigit(0, 1, ((value / 100) % 10), false);
      lc.setDigit(0, 0, ((value / 1000) % 10), false);
    }
  }
  //negatif
  if (value < 0)
  {
    if (value >= -10)
    {
      lc.setDigit(0, 3, (abs(value) % 10), false);
      lc.setRow(0, 2, B00000001);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 0, B00000000);
    }
    if (value >= -100 && value <= -10)
    {
      lc.setDigit(0, 3, (abs(value) % 10), false);
      lc.setDigit(0, 2, ((abs(value) / 10) % 10), false);
      lc.setRow(0, 1, B00000001);
      lc.setRow(0, 0, B00000000);
    }
    if (value >= -1000 && value <= -100)
    {
      lc.setDigit(0, 3, (abs(value) % 10), false);
      lc.setDigit(0, 2, ((abs(value) / 10) % 10), false);
      lc.setDigit(0, 1, ((abs(value) / 100) % 10), false);
      lc.setRow(0, 0, B00000001);
    }
  }
}
