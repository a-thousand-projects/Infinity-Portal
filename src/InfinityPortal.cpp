#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ClickEncoder.h>
#include "EveryTimerB.h"
#include "config.h"
#include "PixelRing.h"
#include "pixelRace.h"
#include "menu.h"
#include "mainMenu.h"

#define PROG 1

ClickEncoder  rotaryOne(ENCODER_ONE_PIN_1,ENCODER_ONE_PIN_2,ENCODER_ONE_SW,ENCODER_STEPS);
ClickEncoder  rotaryTwo(ENCODER_TWO_PIN_1,ENCODER_TWO_PIN_2,ENCODER_TWO_SW,ENCODER_STEPS);
ClickEncoder  rotaryThree(ENCODER_THREE_PIN_1,ENCODER_THREE_PIN_2,ENCODER_THREE_SW,ENCODER_STEPS);
ClickEncoder  rotaryFour(ENCODER_FOUR_PIN_1,ENCODER_FOUR_PIN_2,ENCODER_FOUR_SW,ENCODER_STEPS);


EveryTimerB TimerRotary;


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

volatile uint32_t heartBeat = 0;

#define BTN_STATE_LOW LOW
#define BTN_STATE_HIGH HIGH


uint8_t SettingMode;
uint32_t lastDebounceTime;
uint8_t btnState;
unsigned long delayTime;
uint8_t newSpeed;

PixelRing pixelRing;
PixelRace pixelRace(&pixelRing,0,NUMPIXELS);

Menu menu (&pixelRing);


PixelProgram * currentPixelProgram;

//------- LOCAL PROTOTYPES -------------
void changeMode();

void rotaryTimer()
{
  heartBeat++;
  if (heartBeat > 500)
  {
    uint8_t l = digitalRead(LED_BUILTIN);
    digitalWrite(LED_BUILTIN,!l);
    heartBeat = 0;
  }

 rotaryOne.service();
 rotaryTwo.service();
 rotaryThree.service();
 rotaryFour.service();

}

void doSomething(int menuId)
{
  if (currentPixelProgram != &menu)
  {
    Serial.println("Back to menu");
    menu.Begin();
    currentPixelProgram = &menu;
  }
  else{
    menuItem_t* selectedMenu = menu.GetSelectedMenu();
    Serial.print("Menu Selected = ");Serial.println(selectedMenu->Itemname);
    selectedMenu->program->Begin();
    currentPixelProgram = selectedMenu->program;

  }
  
  
}

// ------- SET UP ---------------
void setup() {

pinMode(LED_BUILTIN,OUTPUT);
digitalWrite(LED_BUILTIN,0);
 TimerB2.initialize();
 TimerB2.attachInterrupt(rotaryTimer);
 TimerB2.setPeriod(1000);

  // Set up Menu Callback
  menu.AttachCallBack(doSomething);

  lastDebounceTime = 0;
  btnState = BTN_STATE_HIGH;

  // Set up Audio Pin
  pinMode(A0, INPUT);
  delayTime = 0;
  Serial.begin(115200);
  Serial.println("Starting");

  pixelRing.begin();

  MainMenu.MenuItems[0].program = (PixelProgram*)&pixelRace;

  menu.SetMenu(&MainMenu);
  menu.Begin();

  currentPixelProgram = &menu;

}

void RotaryLoop()
{
  currentPixelProgram->SetValueOne(rotaryOne.getValue());
  currentPixelProgram->SetValueTwo(rotaryTwo.getValue());
  currentPixelProgram->SetValueThree(rotaryThree.getValue());
  currentPixelProgram->SetValueFour(rotaryFour.getValue());
  ClickEncoder::Button buttorFour = rotaryFour.getButton();

  if (buttorFour != ClickEncoder::Open)
  {
    switch (buttorFour) {
      case ClickEncoder::Pressed: Serial.println("Pressed"); currentPixelProgram->Clicked(4);break;
      case ClickEncoder::Held: Serial.println("Held"); currentPixelProgram->Clicked(4);break;
      case ClickEncoder::Released:Serial.println("Released"); currentPixelProgram->Clicked(4);break;
      case ClickEncoder::Clicked:Serial.println("Clicked"); currentPixelProgram->Clicked(4);break;
      case ClickEncoder::DoubleClicked:Serial.println("Double Click"); currentPixelProgram->Clicked(4);break;
    }
  }
}

uint16_t audio;

void loop(){


speed = 100;

 //   audio = analogRead(AUDIO_PIN);
    RotaryLoop();


  //    if (millis()-delayTime> ((speed)))
      {
        currentPixelProgram->RunStep();
        delayTime = millis();
      } 
}
