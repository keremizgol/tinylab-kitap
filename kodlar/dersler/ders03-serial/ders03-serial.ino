//LED pinleri
#define led1 13
#define led2 12
#define led3 11
#define led4 10

void setup()
{
  //LED pinlerini cikis olarak ayarla
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  //seri iletisimi 9600 baud'da baslat
  Serial.begin(9600);
  //seri monitor acilana kadar bekle
  while (! Serial);
  Serial.print("1 ile 4 arasinda bir LED numarasi girin veya ");
  Serial.println("x ile hepsini sondurun");
}

void loop()
{
  if (Serial.available()) //seri monitor acilana kadar bekle
  {
    char ch = Serial.read(); //seri porttan gelen karakteri oku
    switch (ch) //karaktere gore LED'leri yak
    {
      case '1':
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial.println("1 numarali LED yandi");
        break;
      case '2':
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial.println("2 numarali LED yandi");
        break;
      case '3':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, LOW);
        Serial.println("3 numarali LED yandi");
        break;
      case '4':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH);
        Serial.println("4 numarali LED yandi");
        break;
      case 'x':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial.println("Tum LED'ler sondu");
        break;
      default: //hatali karakter girisinde uyari yap
        Serial.println("Yanlis giris yapildi.");
        break;
    }
  }
}
