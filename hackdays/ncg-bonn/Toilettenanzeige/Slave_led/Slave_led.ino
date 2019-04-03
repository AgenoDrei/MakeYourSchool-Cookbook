/*
 * FM.h
 * A library for SeeedStudio Grove FM
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Steve Chang
 * Create Time: JULY 2014
 * Change Log : Modified by loovee 2013-10-29  ,   Modified by jacob yan 2014-7-29
 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */



#include <SoftwareSerial.h>   //Software Serial Port
#include "LPD8806.h"

#define RxD         6
#define TxD         7

#define PINLED      5

//#define AxD         2     //Var dec Added
//#define BxD         3     //Var dec Added

//#define PINLED      1   //Control? Added

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1
// Number of RGB LEDs in strand:
int nLEDs = 11;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 3;
int clockPin = 2;
int incomingByte = 0;  // for incoming serial data
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
int task;

SoftwareSerial blueToothSerial(RxD,TxD); //Var Added 

void setupBlueToothConnection()
{  

  
  blueToothSerial.begin(9600);  
  
  blueToothSerial.print("AT");
  delay(400); 

  blueToothSerial.print("AT+DEFAULT");             // Restore all setup value to factory setup
  delay(2000); 
  
  blueToothSerial.print("AT+NAMESeeedBTSlave");    // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
  delay(400);
  
    blueToothSerial.print("AT+PIN0000");             // set the pair code to connect 
  delay(400);
  
  blueToothSerial.print("AT+AUTH1");             //
    delay(400);    

    blueToothSerial.flush();

}


void setup(){
   Serial.begin(9600);
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
  //  pinMode(AxD, INPUT);        //Funktion Added
  //  pinMode(BxD, OUTPUT);       //Funktion Added
    pinMode(PINLED, OUTPUT);
    LEDOFF();
    
    setupBlueToothConnection();
}

void loop()
{
    char recvChar;
    
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
   
             // Pixel an stelle(0-11), Rot (0-255), Grün(0-255), Blau(0-255)

             strip.show();
              delay(1000);
              // send data only when you receive data:
               if(blueToothSerial.available() > 0) {
                // read the incoming byte:
                byte led = blueToothSerial.read()-48;
                blueToothSerial.read();
                byte color = blueToothSerial.read()-48;
                blueToothSerial.read();
                // say what you got:
                Serial.print("led: ");
                Serial.println(led, DEC);
                Serial.print("color: ");
                Serial.println(color, DEC);

                if (color==1){
                  strip.setPixelColor(led, strip.Color(0,200,0));
                }
                else{
                  strip.setPixelColor(led, strip.Color(200,0,0));
                }
        }
    }
  }
}




/***************************************************************************
 * Function Name: setupBlueToothConnection
 * Description:  initilizing bluetooth connction
 * Parameters: 
 * Return: 
***************************************************************************/
