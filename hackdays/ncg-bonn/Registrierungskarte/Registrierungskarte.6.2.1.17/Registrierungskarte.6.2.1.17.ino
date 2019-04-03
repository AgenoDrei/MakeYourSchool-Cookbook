/*
  link between the computer and the SoftSerial Shield
  at 9600 bps 8-N-1
  Computer is connected to Hardware UART
  SoftSerial Shield is connected to the Software UART:D2&D3
*/

#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <map>
#include <string>
 
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0;                    // counter for buffer array
String user;
std::map<String, String> names;

rgb_lcd lcd;
const int colorR = 0;
const int colorG = 0;
const int colorB = 0;

void setup()  
{
    SoftSerial.begin(9600);     // the SoftSerial baud rate
    Serial.begin(9600);         // the Serial port of Arduino baud rate.
    Serial.write("begin:\n");
    
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    lcd.clear();
    lcd.setCursor(0,0);

    names["04004B151248"] = "Trung ^.^";
    names["1D00CC831D4F"] = "Malik"; 
    names["1C0031EC2FEE"] = "Jan :3 ";
    names["1C0032772A73"] = "Cara ";
    names["04006EF935A6"] = "Celine x3";
    names["04006EF9CD5E"] = "Layali";
    names["1D00CBF10423"] = "Wilkommen am NCG";
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
           user.trim();
           Serial.println(user);
           Serial.println(names[user.substring(1, 13)]);
            if (user.substring(1,13) == "04004B151248"){
              lcd.setRGB(255, 0, 100); 
            } else if (user.substring(1,13) == "04006EF935A6") {
              lcd.setRGB(148, 0, 255);
            } else if (user.substring(1,13) == "04006EF9CD5E") {
              lcd.setRGB(72, 209, 204);
            } else if (user.substring(1,13) == "1C0032772A73") {
              lcd.setRGB(255, 105, 180);
            } else if (user.substring(1,13) == "1C0031EC2FEE") {
              lcd.setRGB(255, 215, 0);
            } else if (user.substring(1,13) == "1D00CC831D4F") {
              lcd.setRGB(0, 0 , 255);
            } else if (user.substring(1,13) == "1D00CBF10423") {
              lcd.setRGB(255, 0 , 0);
            
            }
            lcd.print(names[user.substring(1, 13)]);
        }
        //Serial.write(buffer, count);     // if no data transmission ends, write buffer to hardware serial port
        clearBufferArray();             // call clearBufferArray function to clear the stored data from the array
        count = 0;                      // set counter of while loop to zero
    }
    if (Serial.available())             // if data is available on hardware serial port ==> data is coming from PC or notebook
    SoftSerial.write(Serial.read());    // write it to the SoftSerial shield
 
    if (user.substring(1,13) == "04004B151248"){
      lcd.setRGB(150, 50, 250); 
    }
  }

void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}
