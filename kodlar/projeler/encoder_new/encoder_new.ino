/* Read Quadrature Encoder
    Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.

    Sketch by max wolf / www.meso.net
    v. 0.1 - very basic functions - mw 20061220

*/


int val;
int encoder0PinA = 7;
int encoder0PinB = 6;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  pinMode (encoder0PinA, INPUT_PULLUP);
  pinMode (encoder0PinB, INPUT_PULLUP);
  Serial.begin (9600);
}

void loop() {
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) 
  {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    Serial.println(encoder0Pos);
  }
  encoder0PinALast = n;
  if(analogRead(A5) >= 80 && analogRead(A5) <= 100)
  {
    encoder0Pos = 0;
  }
}
