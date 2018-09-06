const int AOUTpin=0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int DOUTpin=7;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;


#include <LCD5110_Graph.h>


int sensorValue;
float sonuc;
//     SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
LCD5110 myGLCD(8,9,10,11,12);

extern uint8_t SmallFont[];
extern uint8_t BigNumbers[];



void setup() {


 myGLCD.InitLCD();
 
Serial.begin(9600);//sets the baud rate
pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

void loop()
{
value= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin
limit= digitalRead(DOUTpin);//reads the digital value from the alcohol sensor's DOUT pin

  myGLCD.update();
  sensorValue = analogRead(AOUTpin);
  sonuc = (sensorValue*1.26)/450 ;
  // 200 DEĞERİ REFERANS ALINMIŞTIR
  myGLCD.setFont(SmallFont);        
  myGLCD.print("your Alchol ",CENTER,10); 
  myGLCD.print("mg/L",RIGHT,40); 
  
  
  myGLCD.setFont(BigNumbers);
   myGLCD.printNumF(sonuc,2,5,20);
 
  
  delay(2000);

  myGLCD.update();

Serial.print("Alcohol value: ");
Serial.println(value);//prints the alcohol value


Serial.print("Limit: ");
Serial.print(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
delay(100);
if (limit == HIGH){
digitalWrite(ledPin, LOW);//if limit has been reached, LED turns on as status indicator
}
else{
digitalWrite(ledPin, HIGH);//if threshold not reached, LED remains off
}
}
