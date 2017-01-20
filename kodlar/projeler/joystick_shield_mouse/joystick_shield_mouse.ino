#include <Mouse.h>

#define joy_x A0
#define joy_y A1
#define btn_a 2
#define btn_b 3
#define btn_c 4
#define btn_d 5
#define btn_e 6
#define btn_f 7
#define btn_joy 8

int pos_x = 0;
int pos_y = 0;
bool a_btn = 0;
bool b_btn = 0;
bool c_btn = 0;
bool d_btn = 0;
bool e_btn = 0;
bool f_btn = 0;
bool joy_btn = 0;

void setup()
{
  for (int i = 2; i >= 8; i++)
  {
    pinMode(i, INPUT);
  }
  Serial.begin(115200);
  Mouse.begin();
}

void loop()
{
  readValues();
  Serial.print(pos_x);
  Serial.print(",");
  Serial.print(pos_y);
  Serial.print(",");
  Serial.print(a_btn);
  Serial.print(",");
  Serial.print(b_btn);
  Serial.print(",");
  Serial.print(c_btn);
  Serial.print(",");
  Serial.print(d_btn);
  Serial.print(",");
  Serial.print(e_btn);
  Serial.print(",");
  Serial.print(f_btn);
  Serial.print(",");
  Serial.println(joy_btn);
}

void readValues()
{
  pos_x = analogRead(joy_x);
  pos_y = analogRead(joy_y);
  a_btn = digitalRead(btn_a);
  b_btn = digitalRead(btn_b);
  c_btn = digitalRead(btn_c);
  d_btn = digitalRead(btn_d);
  e_btn = digitalRead(btn_e);
  f_btn = digitalRead(btn_f);
  joy_btn = digitalRead(btn_joy);
  delay(50);
}

