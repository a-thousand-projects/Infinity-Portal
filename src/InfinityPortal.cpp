#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ATPRotary.h>
#include "config.h"
#include "PixelRing.h"
#include "pixelRace.h"
#include "menu.h"
#include "mainMenu.h"

#define PROG 1

// Encoder Pins
ATPRotary rotaryOne(ENCODER_ONE_PIN_1,ENCODER_ONE_PIN_2,ENCODER_ONE_SW);
ATPRotary rotaryTwo(ENCODER_TWO_PIN_1,ENCODER_TWO_PIN_2,ENCODER_TWO_SW);
ATPRotary rotaryThree(ENCODER_THREE_PIN_1,ENCODER_THREE_PIN_2,ENCODER_THREE_SW);
ATPRotary rotaryFour(ENCODER_FOUR_PIN_1,ENCODER_FOUR_PIN_2,ENCODER_FOUR_SW);

int rEcouderCount =0;
// Limits
#define SPEED_MIN   0
#define SPEED_MAX   100

#define COLOUR_MIN 0
#define COLOUR_MAX 255

long positionColour  = -999;
long positionSetting = -999;

int pinVal;

int leader = 0;

char output[100];
uint32_t backColor;

uint8_t red;
uint8_t blue;
uint8_t green;
uint8_t speed = 50;


#define BTN_STATE_LOW LOW
#define BTN_STATE_HIGH HIGH


uint8_t SettingMode;
uint32_t lastDebounceTime;
uint8_t btnState;
unsigned long delayTime;
uint8_t newSpeed;

PixelRing pixelRing;
PixelRace pixelRace;
Menu menu;

PixelProgram * currentPixelProgram;

//------- LOCAL PROTOTYPES -------------
void changeMode();


// ------- SET UP ---------------
void setup() {
  lastDebounceTime = 0;
  btnState = BTN_STATE_HIGH;

  // Set up Audio Pin
  pinMode(A0, INPUT);
  delayTime = 0;
  Serial.begin(115200);
  Serial.println("Starting");

  pixelRing.begin();

  menu.SetMenu(&MainMenu);
  menu.Begin(0,72,&pixelRing);
  //pixelRace.begin(0,72,pixelRing.pixels);
  //pixelRace.SetBackgroundColour(pixelRing.pixels->Color(20,20,20));
  
  //currentPixelProgram = &pixelRace;
  
  currentPixelProgram = &menu;
  rotaryFour.setPushButtonCallBack(changeMode);
  
  rEcouderCount = 0;



}

void doubleClick()
{
  Serial.println("Double Click");
 // changeMode();
}



void changeMode()
{
  Serial.println("Change Mode");
 
}


int setRotaryValue(ATPRotary *rotary,String name,int value, int min, int max)
{
  int oldValue = value;
  int newValue = value;
  int8_t r = (*rotary).rotate();


    if (((oldValue + r) <= max && (oldValue + r) >= min) && r !=0) 
    {
      newValue += r;
      if (newValue != oldValue)
      {
        Serial.print(name + ": "); Serial.println(newValue);
      }

    }     
    return newValue;
}

void RotaryLoop()
{
  rotaryFour.push();
  currentPixelProgram->SetValueOne(rotaryOne.rotate());
  currentPixelProgram->SetValueTwo(rotaryTwo.rotate());
  currentPixelProgram->SetValueThree(rotaryThree.rotate());
  currentPixelProgram->SetValueFour(rotaryFour.rotate());

  //speed = setRotaryValue(&rotaryFour,"Speed",speed,SPEED_MIN,SPEED_MAX);
}

uint16_t audio;

void loop(){
    
speed = 100;

    audio = analogRead(AUDIO_PIN);
    


    RotaryLoop();
    
      if (millis()-delayTime> ((speed)))
      {
       currentPixelProgram->RunStep();
        delayTime = millis();
      }
      

        
   

}
