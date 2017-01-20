//sensor pinleri
#define pot_pin A0
#define ldr_pin A2
#define lm35_pin A3

void setup()
{
  //seri iletisimi 9600 baud'da baslat
  Serial1.begin(9600);
  //seri monitor acilana kadar bekle
  while (! Serial1);
  Serial1.println("XBee kablosuz haberlesme ornegi.");
  delay(3000);
}

void loop()
{
  //potansiyometreyi oku
  int pot_val = analogRead(pot_pin);
  //ldr yi oku ve degeri lux e cevir
  int ldr_val = ((2500.0 / (analogRead(ldr_pin) * (5.0 / 1024.0))) - 500) / 10.0;  
  //lm35 i oku ve degeri santigrada cevir
  int lm35_val = (5.0 * analogRead(lm35_pin) * 100.0) / 1024;
  Serial1.print("Potansiyometre degeri: ");
  Serial1.println(pot_val);
  Serial1.print("LDR degeri: ");
  Serial1.println(ldr_val);
  Serial1.print("Sicaklik degeri: ");
  Serial1.println(lm35_val);
  delay(500);
}
