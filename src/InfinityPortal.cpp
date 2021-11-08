#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//#include <ATPRotary.h>
#include <ClickEncoder.h>
#include "EveryTimerB.h"
#include "config.h"
#include "PixelRing.h"
#include "pixelRace.h"
#include "menu.h"
#include "mainMenu.h"

#define PROG 1

// Encoder Pins


ClickEncoder  rotaryOne(ENCODER_ONE_PIN_1,ENCODER_ONE_PIN_2,ENCODER_ONE_SW,ENCODER_STEPS);
ClickEncoder  rotaryTwo(ENCODER_TWO_PIN_1,ENCODER_TWO_PIN_2,ENCODER_TWO_SW,ENCODER_STEPS);
ClickEncoder  rotaryThree(ENCODER_THREE_PIN_1,ENCODER_THREE_PIN_2,ENCODER_THREE_SW,ENCODER_STEPS);
ClickEncoder  rotaryFour(ENCODER_FOUR_PIN_1,ENCODER_FOUR_PIN_2,ENCODER_FOUR_SW,ENCODER_STEPS);


EveryTimerB TimerRotary;

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

volatile uint32_t test = 0;

#define BTN_STATE_LOW LOW
#define BTN_STATE_HIGH HIGH


uint8_t SettingMode;
uint32_t lastDebounceTime;
uint8_t btnState;
unsigned long delayTime;
uint8_t newSpeed;

PixelRing pixelRing;
PixelRace pixelRace(&pixelRing);
Menu menu (&pixelRing);

PixelProgram * currentPixelProgram;

//------- LOCAL PROTOTYPES -------------
void changeMode();




void rotaryTimer()
{
  test++;
  if (test > 500)
  {
    uint8_t l = digitalRead(LED_BUILTIN);
    digitalWrite(LED_BUILTIN,!l);
    test = 0;
  }

 //rotaryOne.service();
 //rotaryTwo.service();
 rotaryThree.service();
 //rotaryFour.service();
 //test++;
}


// ------- SET UP ---------------
void setup() {

pinMode(LED_BUILTIN,OUTPUT);
digitalWrite(LED_BUILTIN,0);
 TimerB2.initialize();
 TimerB2.attachInterrupt(rotaryTimer);
 TimerB2.setPeriod(1000);
 //TimerRotary.Start();

  lastDebounceTime = 0;
  btnState = BTN_STATE_HIGH;

  // Set up Audio Pin
  pinMode(A0, INPUT);
  delayTime = 0;
  Serial.begin(115200);
  Serial.println("Starting");

  pixelRing.begin();

  menu.SetMenu(&MainMenu);
  menu.Begin();

  //pixelRace.begin(0,72,pixelRing.pixels);
  //pixelRace.SetBackgroundColour(pixelRing.pixels->Color(20,20,20));
  //currentPixelProgram = &pixelRace;
  
  currentPixelProgram = &menu;
  //rotaryFour.setPushButtonCallBack(changeMode);
  
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



void RotaryLoop()
{
 // rotaryFour.push();
  currentPixelProgram->SetValueOne(rotaryOne.getValue());
  currentPixelProgram->SetValueTwo(rotaryTwo.getValue());
  currentPixelProgram->SetValueThree(rotaryThree.getValue());
  currentPixelProgram->SetValueFour(rotaryFour.getValue());
}

uint16_t audio;

void loop(){
    int16_t r1 = rotaryThree.getValue();
    if (r1 != 0) Serial.println(r1);

speed = 10;

 //   audio = analogRead(AUDIO_PIN);
    RotaryLoop();

 // uint8_t p1 = digitalRead(ENCODER_FOUR_PIN_1);
 // uint8_t p2 = digitalRead(ENCODER_FOUR_PIN_2);
 // Serial.print("P1: ");Serial.print(p1);Serial.print(" P2: "); Serial.println(p2);

      if (millis()-delayTime> ((speed)))
      {
 //      currentPixelProgram->RunStep();
        delayTime = millis();
      } 
}
