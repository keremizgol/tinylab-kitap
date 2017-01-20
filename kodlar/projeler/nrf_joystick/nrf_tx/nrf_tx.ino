//Gerekli kutuphaneler: SPI haberlesme icin SPI.h,
//nRF24L01 modulu icin nRF24L01p.h
#include <SPI.h>
#include <nRF24L01p.h>

//nRF24L01 modulunun joystick shield uzerindeki CE ve CSN pin baglantilari
#define CE_PIN 9
#define CSN_PIN 10

//joystick shield uzerindeki butonlar ve eksenler
#define x_axis A0 // x ekseni
#define y_axis A1 //y y ekseni
#define button1 8 // joystick butonu
#define button2 2 // A butonu
#define button3 3 // B butonu
#define button4 4 // C butonu
#define button5 5 // D butonu
#define button6 6 // E butonu
#define button7 7 // F butonu

nRF24L01p transmitter(CSN_PIN, CE_PIN); //CSN,CE

//haberlesmede kullanilacak veriyi String tipinde bir degiskende tutuyoruz
String dataString = "";

void setup()
{
  delay(150);
  //SPI haberlesmeyi baslat
  SPI.begin();
  //SPI haberlesmede bit sirasini en anlamli bit (MSB) ilk gelecek sekilde ayarla
  SPI.setBitOrder(MSBFIRST);
  //nRF modulunun haberlesme kanalini 90 olarak ayarla
  transmitter.channel(90);
  //verici rolundeki nRF modulunun adresini tiny olarak belirliyoruz
  transmitter.TXaddress("tiny");
  //vericiyi baslat
  transmitter.init();
}

void loop()
{
  //baslangic karakteri
  dataString += "$";
  //x ekseni degeri 1000'den kucuk ise bir 0 ekle
  if(analogRead(x_axis) < 1000) dataString += "0";
  //x ekseni degeri 100'den kucuk ise bir 0 ekle
  if(analogRead(x_axis) < 100) dataString += "0";
  //x ekseni degeri 10'dan kucuk ise bir 0 ekle
  if(analogRead(x_axis) < 10) dataString += "0";
  //x ekseni degerini gonderilecek String'e ekle
  dataString += String(analogRead(x_axis));
  dataString += ",";
  //y ekseni degeri 1000'den kucuk ise bir 0 ekle
  if(analogRead(y_axis) < 1000) dataString += "0";
  //y ekseni degeri 100'den kucuk ise bir 0 ekle
  if(analogRead(y_axis) < 100) dataString += "0";
  //y ekseni degeri 10'dan kucuk ise bir 0 ekle
  if(analogRead(y_axis) < 10) dataString += "0";
  //y ekseni degerini gonderilecek String'e ekle
  dataString += String(analogRead(y_axis));
  dataString += ",";
  //buton1 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button1));
  dataString += ",";
  //buton2 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button2));
  dataString += ",";
  //buton3 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button3));
  dataString += ",";
  //buton4 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button4));
  dataString += ",";
  //buton5 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button5));
  dataString += ",";
  //buton6 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button6));
  dataString += ",";
  //buton7 degerini gonderilecek String'e ekle
  dataString += String(digitalRead(button7));
  dataString += "#";  
  //String'i gonder
  transmitter.txPL(dataString);
  //gonderme metodu hizli, karsi taraftan alindi mesajini bekleme
  transmitter.send(FAST);
  //String'i bosalt
  dataString = "";
  delay(50);
}
