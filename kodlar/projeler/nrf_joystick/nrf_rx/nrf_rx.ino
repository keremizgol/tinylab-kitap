//Gerekli kutuphaneler: SPI haberlesme icin SPI.h,
//nRF24L01 modulu icin nRF24L01p.h,
//Bilgisayarın Tinylab'i joystick olarak tanıyabilmesi icin Joystick.h
#include <SPI.h>
#include <nRF24L01p.h>
#include <Joystick.h>

//nRF24L01 modulunun Tinylab uzerindeki CE ve CSN pin baglantilari
#define CE_PIN 9
#define CSN_PIN 8

//Joystick kullaninimi icin tanimlama
Joystick_ Joystick;

//varsayilan degerler
int pos_x = 0;
int pos_y = 0;
int a_btn = 0;
int b_btn = 0;
int c_btn = 0;
int d_btn = 0;
int e_btn = 0;
int f_btn = 0;
int joy_btn = 0;

//haberlesmede kullanilacak veriyi String tipinde bir degiskende tutuyoruz
String message;

nRF24L01p receiver(CSN_PIN, CE_PIN); //CSN,CE

void setup()
{
  delay(150);
  //SPI haberlesmeyi baslat
  SPI.begin();
  //SPI haberlesmede bit sirasini en anlamli bit (MSB) ilk gelecek sekilde ayarla
  SPI.setBitOrder(MSBFIRST);
  //USB joystick olarak tanit
  Joystick.begin();
  //nRF modulunun haberlesme kanalini 90 olarak ayarla
  receiver.channel(90);
  //alici rolundeki nRF modulunun adresini tiny olarak belirliyoruz
  receiver.RXaddress("tiny");
  //aliciyi baslat
  receiver.init();
}

void loop()
{
  //nRF modul uzerinden gelen degerleri oku
  readValues();
  //x ekseni degerini joystick olarak bilgisayara bildir
  Joystick.setXAxis(pos_x);
  //y ekseni degerini joystick olarak bilgisayara bildir
  Joystick.setYAxis(pos_y);
  //joystick shield uzerindeki butonlar ters calistigi icin hepsinin tersini aliyoruz
  Joystick.setButton(0, !a_btn);
  Joystick.setButton(1, !b_btn);
  Joystick.setButton(2, !c_btn);
  Joystick.setButton(3, !d_btn);
  Joystick.setButton(4, !e_btn);
  Joystick.setButton(5, !f_btn);
  Joystick.setButton(6, !joy_btn);
}

//nRF24L01 modulunden gelen degerleri degiskenlere tasiyan fonksiyon
void readValues()
{
  if (receiver.available())//nRF modulu takili ise
  {
    //alici modulden gelen mesaji oku
    receiver.read();
    receiver.rxPL(message);
    //gelen mesaji karakter sirasina gore ayir, degiskenlere ata
    //ilk karakter "$", sonraki 4 karakter x ekseni degeri
    String joy_x = message.substring(1, 5);
    //x ekseni degerini int tipine cevir
    pos_x = joy_x.toInt();
    //x ekseni degerinden sonra "," geliyor, sonraki 4 karakter y ekseni degeri
    String joy_y = message.substring(6, 10);
    //y ekseni degerini int tipine cevir
    pos_y = joy_y.toInt();
    //y ekseni degerinden sonra "," geliyor, sonraki 1 karakter a butonu
    String btn_a = message.substring(11, 13);
    //a butonu degerini int tipine cevir
    a_btn = btn_a.toInt();
    //a butonu degerinden sonra "," geliyor, sonraki 1 karakter b butonu
    String btn_b = message.substring(13, 15);
    //b butonu degerini int tipine cevir
    b_btn = btn_b.toInt();
    //b butonu degerinden sonra "," geliyor, sonraki 1 karakter c butonu
    String btn_c = message.substring(15, 17);
    //c butonu degerini int tipine cevir
    c_btn = btn_c.toInt();
    //c butonu degerinden sonra "," geliyor, sonraki 1 karakter d butonu
    String btn_d = message.substring(17, 19);
    //d butonu degerini int tipine cevir
    d_btn = btn_d.toInt();
    //d butonu degerinden sonra "," geliyor, sonraki 1 karakter e butonu
    String btn_e = message.substring(19, 21);
    //e butonu degerini int tipine cevir
    e_btn = btn_e.toInt();
    //e butonu degerinden sonra "," geliyor, sonraki 1 karakter f butonu
    String btn_f = message.substring(21, 23);
    //e butonu degerini int tipine cevir
    f_btn = btn_f.toInt();
    //e butonu degerinden sonra "," geliyor, sonraki 1 karakter joystick butonu
    String btn_joy = message.substring(23, 25);
    //joystick butonu degerini int tipine cevir
    joy_btn = btn_joy.toInt();
    //String'i bosalt
    message = "";
  }
}
