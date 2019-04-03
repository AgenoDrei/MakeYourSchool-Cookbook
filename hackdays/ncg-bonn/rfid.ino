/*
  link between the computer and the SoftSerial Shield
  at 9600 bps 8-N-1
  Computer is connected to Hardware UART
  SoftSerial Shield is connected to the Software UART:D2&D3
*/
 
#include <SoftwareSerial.h>
#include <Wire.h>
#include "rgb_lcd.h"
 
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0;                    // counter for buffer array
String user;

rgb_lcd lcd;
const int colorR = 200;
const int colorG = 100;
const int colorB = 100;
 
void setup()
{
    SoftSerial.begin(9600);     // the SoftSerial baud rate
    Serial.begin(9600);         // the Serial port of Arduino baud rate.
    Serial.write("begin:\n");
    
    lcd.begin(16, 1);
    lcd.setRGB(colorR, colorG, colorB);
    lcd.clear();
    lcd.setCursor(0,0);    
}
 
void loop()
{
    // if date is coming from software serial port ==> data is coming from SoftSerial shield
    if (SoftSerial.available())              
    {
      lcd.clear();
        while(SoftSerial.available())               // reading data into char array
        {
            String user = SoftSerial.readString();
            //buffer[count++] = SoftSerial.read();      // writing data into array
            //if(count == 64)break;
           Serial.println(user);
           lcd.print(user);
        }
        //Serial.write(buffer, count);     // if no data transmission ends, write buffer to hardware serial port
        clearBufferArray();             // call clearBufferArray function to clear the stored data from the array
        count = 0;                      // set counter of while loop to zero
    }
    if (Serial.available())             // if data is available on hardware serial port ==> data is coming from PC or notebook
    SoftSerial.write(Serial.read());    // write it to the SoftSerial shield
  }

void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}
