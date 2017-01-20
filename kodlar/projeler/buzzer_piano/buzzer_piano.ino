#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_C5  523

int button1 = 9;
int button2 = 8;
int buzzerPin = A1;

void setup()
{
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(button1) == LOW)
  {
    tone(buzzerPin, NOTE_C4);
    delay(250);
    noTone(buzzerPin);
  }
  if (digitalRead(button2) == LOW)
  {
    tone(buzzerPin, NOTE_E4);
    delay(250);
    noTone(buzzerPin);
  }
  if (analogRead(A5) >= 200 && analogRead(A5) <= 210)
  {
    tone(buzzerPin, NOTE_G4);
    delay(250);
    noTone(buzzerPin);
  }
  if (analogRead(A5) >= 500 && analogRead(A5) <= 510)
  {
    tone(buzzerPin, NOTE_C5);
    delay(250);
    noTone(buzzerPin);
  }
}

