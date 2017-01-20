#define led1 13
#define led2 12
#define led3 11
#define led4 10

bool led1_s = LOW;
bool led2_s = LOW;
bool led3_s = LOW;
bool led4_s = LOW;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Enter a number between 1-4 to toggle the corresponding LED or enter 'x' to turn off all");
}

void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    switch (ch)
    {
      case '1':
        led1_s = !led1_s;
        Serial.print("LED1 state is: ");
        Serial.println(led1_s);
        break;
      case '2':
        led2_s = !led2_s;
        Serial.print("LED2 state is: ");
        Serial.println(led2_s);
        break;
      case '3':
        led3_s = !led3_s;
        Serial.print("LED3 state is: ");
        Serial.println(led3_s);
        break;
      case '4':
        led4_s = !led4_s;
        Serial.print("LED4 state is: ");
        Serial.println(led4_s);
        break;
      case 'x':
        led1_s = LOW;
        led2_s = LOW;
        led3_s = LOW;
        led4_s = LOW;
        Serial.println("All LEDs are: 0");
        break;
      default:
        Serial.println("Wrong input.");
        break;
    }
    digitalWrite(led1, led1_s);
    digitalWrite(led2, led2_s);
    digitalWrite(led3, led3_s);
    digitalWrite(led4, led4_s);
  }
}
