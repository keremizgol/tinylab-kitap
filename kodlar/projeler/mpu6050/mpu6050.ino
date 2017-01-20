//gerekli kutuphaneler: I2C icin Wire.h,
//I2C LCD icin LiquidTWI2.h
#include <Wire.h>
#include <LiquidTWI2.h>

//MPU6050 sensorun adresi
#define MPU_addr 0x69

//I2C LCD icin tanimlama
LiquidTWI2 lcd(0);

//baslangic degerleri
int AcX = 0;
int AcY = 0;
int AcZ = 0;

void setup()
{
  //I2C LCD icin ayar
  lcd.setMCPType(LTI_TYPE_MCP23008);
  //I2C LCD icin ayar
  lcd.begin(16, 2);
  //arka isigi ac
  lcd.setBacklight(HIGH);
  //I2C iletisimi baslat
  Wire.begin();
  //I2C haberlesme adresini MPU6050'nin adresi olarak belirle
  Wire.beginTransmission(MPU_addr);
  //MPU6050'nin PWR_MGMT_1 register'ina (0x6B adresinde) 0 gondererek sensorun uyanmasini sagliyoruz
  Wire.write(0x6B);
  Wire.write(0);
  //haberlesmeyi bitir
  Wire.endTransmission(true);
}

void loop()
{
  //sensoru oku
  readIMU(MPU_addr);
  //sensor bilgisini ekrana yazdir
  printToLCD();
  //333ms bekle, sensorun guncellenmesi icin optimum sure
  delay(333);
}

//sensoru okuma fonksiyonu
void readIMU(int addr)
{
  //I2C haberlesme adresini MPU6050'nin adresi olarak belirle
  Wire.beginTransmission(addr);
  //ACCEL_XOUT_H registerini (0x3B adresinde) oku
  Wire.write(0x3B);
  //haberlesmeye devam et
  Wire.endTransmission(false);
  //toplam 6 adet register'dan bilgi oku
  Wire.requestFrom(MPU_addr, 6, true);
  //her eksenin bilgisi toplam 2 byte (16-bit) oldugundan iki ayri register'da tutuluyor
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) ve 0x3C (ACCEL_XOUT_L)
  //16-bit veriyi -100 ile +100 arasinda olcekle
  AcX = map(AcX, -32768, 32767, -100, 100);
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) ve 0x3E (ACCEL_YOUT_L)
  //16-bit veriyi -100 ile +100 arasinda olcekle
  AcY = map(AcY, -32768, 32767, -100, 100);
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) ve 0x40 (ACCEL_ZOUT_L)
  //16-bit veriyi -100 ile +100 arasinda olcekle
  AcZ = map(AcZ, -32768, 32767, -100, 100);
}

//ivme verisini LCD ekrana yaz
void printToLCD()
{
  //imleci birinci satir birinci sutuna getir
  lcd.setCursor(0, 0);
  lcd.print("X=");

  //x-ekseni degeri pozitif ise
  if (AcX >= 0)
  {
    //"X=" den sonra "+" isareti koy
    lcd.setCursor(2, 0);
    lcd.print('+');
    //AcX degiskenini basamak basamak LCD'ye yaz
    lcd.setCursor(3, 0);
    lcd.print((AcX / 100) % 10);
    lcd.setCursor(4, 0);
    lcd.print((AcX / 10) % 10);
    lcd.setCursor(5, 0);
    lcd.print(AcX % 10);
  }
  //x-ekseni degeri negatif ise
  if (AcX < 0)
  {
    //"X=" den sonra "-" isareti koy
    lcd.setCursor(2, 0);
    lcd.print('-');
    //AcX degiskenini basamak basamak LCD'ye yaz
    lcd.setCursor(3, 0);
    lcd.print(abs((AcX / 100) % 10));
    lcd.setCursor(4, 0);
    lcd.print(abs((AcX / 10) % 10));
    lcd.setCursor(5, 0);
    lcd.print(abs(AcX % 10));
  }

  //imleci birinci satir onbirinci sutuna getir
  lcd.setCursor(10, 0);
  lcd.print("Y=");
  //y-ekseni degeri pozitif ise
  if (AcY >= 0)
  {
    //"Y=" den sonra "+" isareti koy
    lcd.setCursor(12, 0);
    lcd.print('+');
    //AcY degiskenini basamak basamak LCD'ye yaz
    lcd.setCursor(13, 0);
    lcd.print((AcY / 100) % 10);
    lcd.setCursor(14, 0);
    lcd.print((AcY / 10) % 10);
    lcd.setCursor(15, 0);
    lcd.print(AcY % 10);
  }
  //y-ekseni degeri negatif ise
  if (AcY < 0)
  {
    //"Y=" den sonra "-" isareti koy
    lcd.setCursor(12, 0);
    lcd.print('-');
    lcd.setCursor(13, 0);
    //AcY degiskenini basamak basamak LCD'ye yaz
    lcd.print(abs((AcY / 100) % 10));
    lcd.setCursor(14, 0);
    lcd.print(abs((AcY / 10) % 10));
    lcd.setCursor(15, 0);
    lcd.print(abs(AcY % 10));
  }
  //imleci ikinci satir altinci sutuna getir
  lcd.setCursor(5, 1);
  lcd.print("Z=");
  //z-ekseni degeri pozitif ise
  if (AcZ >= 0)
  {
    //"Z=" den sonra "+" isareti koy
    lcd.setCursor(7, 1);
    lcd.print('+');
    //AcZ degiskenini basamak basamak LCD'ye yaz
    lcd.setCursor(8, 1);
    lcd.print((AcZ / 100) % 10);
    lcd.setCursor(9, 1);
    lcd.print((AcZ / 10) % 10);
    lcd.setCursor(10, 1);
    lcd.print(AcZ % 10);
  }
  //z-ekseni degeri negatif ise
  if (AcZ < 0)
  {
    //"Z=" den sonra "-" isareti koy
    lcd.setCursor(7, 1);
    lcd.print('-');
    //AcZ degiskenini basamak basamak LCD'ye yaz
    lcd.setCursor(8, 1);
    lcd.print(abs((AcZ / 100) % 10));
    lcd.setCursor(9, 1);
    lcd.print(abs((AcZ / 10) % 10));
    lcd.setCursor(10, 1);
    lcd.print(abs(AcZ % 10));
  }
}
