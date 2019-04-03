#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

int Tasterstatus8 = 0;
int Tasterstatus7 = 0;
int Tasterstatus6 = 0;
int Tasterstatus4 = 0;
int Notfalltaster = 7;
int GruenTaster = 6;
int GelbTaster = 8;
int RotTaster = 2;

int LEDanzahl = 14;
int DataPin = 3;
int ClockPin = 4;

int Zustand = 100;

unsigned int Rot = 0;
unsigned int Gelb = 0;
unsigned int Gruen = 0;

LPD8806 strip = LPD8806(LEDanzahl, DataPin, ClockPin);

void setup() {
  pinMode(Notfalltaster, INPUT);
    pinMode(RotTaster, INPUT);
  pinMode(GelbTaster, INPUT);
  pinMode(GruenTaster, INPUT);

  noTone(5);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  // Start up the LED strip
  strip.begin();

for (int i = 0; i<=14; i++)
{
strip.setPixelColor(i,0,Gruen,0);
}
  // Update the strip, to start they are all 'off'
  strip.show();
}

void loop() {

 // Summer
Tasterstatus7 = digitalRead(Notfalltaster);
Tasterstatus6 = digitalRead (GruenTaster);
Tasterstatus4 = digitalRead (RotTaster);
Tasterstatus8 = digitalRead (GelbTaster);



    
if (Tasterstatus7 == HIGH)
{
  for (int i = 0; i<=14; i++)
{
strip.setPixelColor(i,127,0,0);
}
strip.show();

/*Gruen = 0;
Rot = 0;
Gelb = 0;*/

  tone(5, 400);
  delay(300);
  noTone(5);

  Zustand = 100;
  }



// LEDs
//

if (Tasterstatus6 == HIGH)
{

Zustand = Zustand+5;
 if (Gruen > 0 || (Rot == 0 && Gelb == 0))
  {
    
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,Gruen, 0);
    }
    Gruen++;*/
    }
    else if (Rot > 0 && Gruen == 0)
    {
      
    }
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,Rot,0, 0);
    }
    Rot--;*/
      }
       else if (Gelb > 0 && Gruen == 0)
    {
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,Gelb ,Gelb, 0);
    }
    Gelb--;
      }*/
  } 

else if (Tasterstatus8 == HIGH)
{

if (Zustand > 39)
Zustand = Zustand-2;
else if (Zustand < 40)
Zustand = Zustand+2;
  /*if (Gelb > 0 || (Rot == 0 && Gruen == 0))
  {
    
      for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,Gelb,Gelb, 0);
    }
    Gelb++;*/
    }
    else if (Rot > 0 && Gelb == 0)
    {
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,Rot,0, 0);
    }
    Rot--;*/
      }
       else if (Gruen > 0 && Gelb == 0)
    {
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,Gruen, 0);
    }
    Gruen--;
      }*/
}

else if (Tasterstatus4 == HIGH)
{

Zustand = Zustand-5;

  if (Rot > 0 || (Gelb == 0 && Gruen == 0))
  {
    /*Rot++;
    for (int i = 0; i <= 14; i++)
    {
      strip.setPixelColor(i,Rot,0,0);
    }*/
    }
    else if (Gelb > 0 && Rot == 0)
    {
      /*for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,Gelb,Gelb, 0);
    }
    Gelb--;*/
    }
    else if (Gruen > 0 && Gelb == 0)
    {
     /* for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,Gruen, 0);
    }
    Gruen--;*/
    }
}
/*
if (Gelb < 0)
Gelb = 0; 
if (Rot < 0)
Rot = 0;
if (Gruen < 0)
Gruen = 0;*/

if (Zustand > 100)
Zustand = 100;
if (Zustand < 0)
Zustand = 0;

if (Zustand <= 100)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,100, 0);
    }
  }
  if (Zustand <= 95)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,85, 0);
    }
  }
   if (Zustand <= 90)
   {
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,70, 0);
    }
  }
  if (Zustand <= 85)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,55, 0);
    }
  }
  if (Zustand <= 80)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,0,45, 0);
    }
  }
  if (Zustand <= 75)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,1,37, 0);
    }
  }
  if (Zustand <= 70)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,2,30, 0);
    }
  }
  if (Zustand <= 65)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,5,25, 0);
    }
  }
  if (Zustand <= 60)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,7,20, 0);
    }
  }
  if (Zustand <= 55)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,7,12, 0);
    }
  }
  if (Zustand <= 50)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,10,10, 0);
    }
  }
  if (Zustand <= 45)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,20,20, 0);
    }
  }
  if (Zustand <= 40)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,30, 30, 0);
    }
  }
  if (Zustand <= 35)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,30,20, 0);
    }
  }
  if (Zustand <= 30)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,40,20, 0);
    }
  }
  if (Zustand <= 25)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,40,15, 0);
    }
  }
  if (Zustand <= 20)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,40,10, 0);
    }
  }
  if (Zustand <= 15)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,50,7, 0);
    }
  }
  if (Zustand <= 10)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,55,2, 0);
    }
  }
  if (Zustand <= 5)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,70,0, 0);
    }
  }
  if (Zustand == 0)
{
  for (int i = 0; i <= 14; i++)
    {
    strip.setPixelColor(i,100,0, 0);
    }
  }
  

strip.show();

delay (200);
}
