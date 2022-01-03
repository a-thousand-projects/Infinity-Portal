#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

//#include "EveryTimerB.h"
#include "config.h"
#include "PixelRing.h"
#include "pixelRace.h"
#include "RandomChaos.h"
#include "menu.h"
#include "mainMenu.h"
#include <ArduinoLog.h>
#include <AceButton.h>

using namespace ace_button;

#define PROG 1



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


// buttons
AceButton button_1(BTN_1);
AceButton button_2(BTN_2);
AceButton button_3(BTN_3);
AceButton button_Up(BTN_UP);
AceButton button_Down(BTN_DOWN);


uint8_t SettingMode;
uint32_t lastDebounceTime;
uint8_t btnState;

uint8_t newSpeed;

PixelRing pixelRing;
// Set up Pixel Programs
PixelRace pixelRace(&pixelRing,0,NUMPIXELS);
RandomChaos randomChaos (&pixelRing);

Menu menu (&pixelRing);


PixelProgram * currentPixelProgram;

//------- LOCAL PROTOTYPES -------------
void changeMode();



void buttonCallBack(int menuId)
{
  if (menuId == -1)
  {
     currentPixelProgram = &menu;
     currentPixelProgram->Begin();
     return;
  }

  if (currentPixelProgram != &menu)
  {
    Log.infoln("Back to menu");
    menu.Begin();
    currentPixelProgram = &menu;
  }
  else{
    menuItem_t* selectedMenu = menu.GetSelectedMenu();
    if (!selectedMenu->program)
    {
      Log.infoln("No Program attached to menu");
      return;
    }
    Log.info("Menu Selected = %s" CR,selectedMenu->Itemname.c_str());
    selectedMenu->program->Begin();
    currentPixelProgram = selectedMenu->program;

  }
  
  
}

void ButtonEventHandler(AceButton*  button , uint8_t eventType,uint8_t  buttonState )
{
  Log.info("Event %i" CR,eventType);
  uint8_t btn = button->getPin();
  switch (eventType) {
    
    case AceButton::kEventClicked:
      Log.info("Button %d Clicked" CR,btn);
        currentPixelProgram->Clicked(btn);
      break;
    case AceButton::kEventLongPressed:
      Log.info("Button %d LONG Pressed" CR,btn);
      currentPixelProgram->LongPress(btn);
      break;
  }
}

// ------- SET UP ---------------
void setup() {
 // Set up Serial Port
 Serial.begin(115200);
 // Set up logging
 Log.begin(LOG_LEVEL_VERBOSE,&Serial);
 Log.setShowLevel(true);
 Log.notice("Infinity Portal Starting up" CR);

 pinMode(LED_BUILTIN,OUTPUT);
 digitalWrite(LED_BUILTIN,0);


  // Set up buttons
  pinMode(BTN_1,INPUT_PULLUP);
  pinMode(BTN_2,INPUT_PULLUP);
  pinMode(BTN_3,INPUT_PULLUP);
  pinMode(BTN_UP,INPUT_PULLUP);
  pinMode(BTN_DOWN,INPUT_PULLUP);

  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(ButtonEventHandler);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  



  // Set up Menu Callback
  menu.AttachCallBack(buttonCallBack);
  pixelRace.AttachCallBack(buttonCallBack);
  randomChaos.AttachCallBack(buttonCallBack);
  lastDebounceTime = 0;
  btnState = BTN_STATE_HIGH;

  // Set up Audio Pin
  pinMode(A0, INPUT);

  

  pixelRing.begin();

  MainMenu.MenuItems[0].program = (PixelProgram*)&pixelRace;
  MainMenu.MenuItems[1].program = (PixelProgram*)&randomChaos;
  menu.SetMenu(&MainMenu);
  menu.Begin();

  currentPixelProgram = &menu;

}




uint16_t audio;

void ButtonCheck(){
  button_1.check();
  button_2.check();
  button_3.check();
  button_Up.check();
  button_Down.check();
}

void loop(){

  ButtonCheck();
 //   audio = analogRead(AUDIO_PIN);
  currentPixelProgram->RunStep();
}
