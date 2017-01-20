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
  //HC06 ile seri iletisimi 9600 baud'da baslat
  Serial1.begin(9600);
  Serial1.print("1 ile 4 arasinda bir LED numarasi girin veya ");
  Serial1.println("x ile hepsini sondurun");
}

void loop()
{
  if (Serial1.available()) //Haberlesme baslayana kadar bekle
  {
    char ch = Serial1.read(); //Bluetooth uzerinden gelen karakteri oku
    switch (ch) //karaktere gore LED'leri yak
    {
      case '1':
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial1.println("1 numarali LED yandi");
        break;
      case '2':
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial1.println("2 numarali LED yandi");
        break;
      case '3':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, LOW);
        Serial1.println("3 numarali LED yandi");
        break;
      case '4':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH);
        Serial1.println("4 numarali LED yandi");
        break;
      case 'x':
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        Serial1.println("Tum LED'ler sondu");
        break;
      default: //hatali karakter girisinde uyari yap
        Serial1.println("Yanlis giris yapildi.");
        break;
    }
  }
}
