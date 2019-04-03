#include <Wire.h>
#include <SeeedOLED.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
int Taster1=2;
int Taster2=5;
int Tasterstatus1=0;
int Tasterstatus2=0;
int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;
int Anzahl = 0;
int Tastergedruckt = 0;
void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display
  servo1.attach(8);
  servo1.write(0);
  servo2.attach(4);
  servo2.write(0);
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("Auswaehlen"); //Print the String
  pinMode(Taster1, INPUT);
  pinMode(Taster2, INPUT);
  
}

void loop()
{ 
  Tasterstatus1=digitalRead(Taster1);
  Tasterstatus2=digitalRead(Taster2);
  if (Tasterstatus1 == HIGH)
{ 
  Tastergedruckt=1;
  SeeedOled.clearDisplay();   
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Bezahlen1Euro");
}
  if (Tasterstatus2 == HIGH)
{
  Tastergedruckt=2;
  SeeedOled.clearDisplay();   
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Bezahlen50Cent");
}
  if (Tastergedruckt>0)
  {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue < 200)
  { //Münze in der Lichtschranke
    
    Anzahl +=1;
    delay(300);
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("BEZAHLT:");
    SeeedOled.putNumber(Anzahl*50);
    SeeedOled.putString("Cent");
  }
  if (Tastergedruckt == 1 && Anzahl == 2){
    servo1.write(180);
    delay(1000);
    servo1.write(0);
    delay(1000);
    Anzahl=0;
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Auswaehlen");
  }
   if (Tastergedruckt == 2 && Anzahl == 1){
    servo2.write(180);
    delay(1000);
    servo2.write(0);
    delay(1000);
    Anzahl=0;
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Auswaehlen");
  }
 delay(100);
  
}
}
