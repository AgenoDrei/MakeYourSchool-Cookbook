#include <Wire.h>
#include <SeeedOLED.h>

#include <avr/pgmspace.h>

#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>

SoftwareSerial mp3(2, 3);

int counter;
bool isGone;
char* message;

void setup()  {
   Wire.begin();

  mp3.begin(9600);
  Serial.begin(9600);
  
  SelectPlayerDevice(0x02);
  SetVolume(0x1E);
    
  pinMode(6,INPUT);
  pinMode(7, OUTPUT);
  counter = 0;
  isGone = true;
  message = "";
//   SeeedOled.init();  //initialize SEEED Gray OLED display

  SeeedOled.init();  //initialze SEEED OLED display

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("Versp. Pers.:"); //Print the String
  SeeedOled.setTextXY(1,0);
    draw(counter);

}

void loop()  {
  /*if(isGone)
  {
    delay(1000);
    counter++;  
  }*/
  while(1)
  {
        if(digitalRead(6)==LOW)  {
           Serial.println("Somebody is here.");

           counter++;
             draw(counter);
             play();
            tone(7, 200);
            delay(8500);
            noTone(7);
        }
        else  {
            Serial.println("Nobody.");
            noTone(7);
        }
  }
}
void draw(int num)
{
  

//  SeeedOled.clearDisplay();     //Clear Display.

  SeeedOled.setTextXY(1,0);  //set Cursor to 1st line, 0th column
  SeeedOled.putNumber(num); //Print Hello World
  
  
  }
void play()
{
  Serial.println("play");
  SpecifyMusicPlay(1);
}



 
