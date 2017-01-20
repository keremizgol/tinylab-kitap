#define buzzerPin A1

int notaSayisi = 8;

//do, re, mi, fa, sol, la, si ve ince do icin frekans degerleri
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;

//notalarin tamamini array icinde tut
int notalar[] = {C, D, E, F, G, A, B, C_};

void setup()
{
  //0.5sn araliklar ile sirayla notalari cal
  for (int i = 0; i < notaSayisi; i++)
  {
    tone(buzzerPin, notalar[i]);
    delay(500);
    noTone(buzzerPin);
    delay(20);
  }
  noTone(buzzerPin);
}

void loop()
{
}
