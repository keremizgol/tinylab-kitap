//thingspeak.com ip adresi
#define IP "184.106.153.149"
//sicaklik sensoru pin baglantisi
#define lm35_pin A3

//Thingspeak'ten alacaginiz Write API Key
//kodu yuklemeden once degistirmeyi unutmayiniz
String api_key = "xxxxxxxxxxxxxxxx";


void setup()
{
  //USB-seri baglantisi
  Serial.begin(9600);
  //Tinylab-ESP8266 baglantisi
  Serial1.begin(115200);
  delay(5000);
}

void loop() {
  //sicaklik sensorunu oku
  int temp = (5.0 * analogRead(lm35_pin) * 100.0) / 1024;
  //USB-seri portuna sicakligi yaz
  Serial.println(temp);
  //Thingspeak'e sicaklik bilgisini yolla
  send_temp(temp);
  //1 dk bekle
  delay(60000);
}


void send_temp(int temp)
{
  //Thingspeak sunucusuna 80 numarali porttan TCP iletisimini baslat
  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
  Serial1.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
  delay(1000);
  if (Serial1.find("Error")) //baglanti hatasi durumunda seri monitorden bildir
  {
    Serial.println("AT+CIPSTART Error");
    return;
  }

  //sicaklik bilgisi ve Write API Key ile gonderilecek komutu String tipinde bir degiskende tut
  String cmd = "GET /update?key=";
  cmd += api_key;
  cmd += "&field1=";
  cmd += (int(temp));
  cmd += "\r\n\r\n";
  delay(3000);

  //hazirlanan komutun boyutunu cmd.lenght() ile bul
  Serial.print("AT+CIPSEND=");
  Serial1.print("AT+CIPSEND=");
  Serial.println(cmd.length() + 2);
  Serial1.println(cmd.length() + 2);

  delay(1000);

  //komut gonderilmeye hazir ise cmd String'ini gonder
  if (Serial1.find(">"))
  {
    Serial.print(cmd);
    Serial1.print(cmd);
    Serial.print("\r\n\r\n");
    Serial1.print("\r\n\r\n");
  }
  //komut gonderilmeye hazir degil ise baglantiyi kapat
  else
  {
    Serial.println("AT+CIPCLOSE");
    Serial1.println("AT+CIPCLOSE");
  }
}
