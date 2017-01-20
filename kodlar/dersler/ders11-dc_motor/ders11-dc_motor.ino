//motor surucu dijital pin 5 e bagli
#define motorPin 5

//baslangic degerleri
int hiz = 0;
 
void setup() 
{ 
  //motor surucu pinini cikis olarak ayarla
  pinMode(motorPin, OUTPUT);
} 
  
void loop() 
{ 
  //0 dan 255 e kadar kademeli olarak motorun hizini arttir
  for(hiz = 0; hiz <= 255; hiz++) 
  {                                  
    analogWrite(motorPin,hiz);
    delay(20);                       
  } 
  //255 e ulasinca motoru yavaslatarak durdur
  for(hiz = 255; hiz>=0; hiz--)
  {                                
    analogWrite(motorPin,hiz);          
    delay(20);                    
  } 
}
