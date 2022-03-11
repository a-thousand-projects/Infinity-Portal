#include <arduino.h>
#include "pixelColourWarp.h"
#include "pixelProgram.h"
#include <ArduinoLog.h>
#include "pixelRing.h"

PixelColourWarp::PixelColourWarp(PixelRing *pr):PixelProgram(pr)
{

}


void PixelColourWarp::RunStep()
{
unsigned long tm;
led = 0;


  do {

    angle = step * led;
    rad = (((angle)))*((M_PI /180));

    green = cos((rad*1) +(pulse*1))+0.5;
    blue = cos((rad*1 + (M_PI/2)) +(pulse*2)) + 0.5;
    red = (cos((rad*1)  + (M_PI)-pulse*3)) + 0.5;

if (red <0) red = 0;
    if (green < 0 ) green = 0;
    if (blue< 0 ) blue = 0;
      
      redLEDValue = (255 * (red/2));
      greenLEDValue = (255 * (green/2));
      blueLEDValue = (255 * (blue/2));
      pixelRing->neoPixels->setPixelColor(led,pixelRing->neoPixels->Color(redLEDValue ,greenLEDValue ,blueLEDValue));
      
     led ++;

    } while (led < ledCount);
    pixelRing->neoPixels->show();
   // delay(10);

    pulse += (M_PI/ledCount);
}


void PixelColourWarp::SetValueOne(int16_t value)
{}

void PixelColourWarp::SetValueTwo(int16_t value)
{}

void PixelColourWarp::SetValueThree(int16_t value)
{}

void PixelColourWarp::ChangeGlobalSpeed(int16_t value)
{}

void PixelColourWarp::SetPulseValues(uint16_t pulseOn, uint16_t pulseOff)
{
   
}

void PixelColourWarp::Begin()
{
    Log.info("Pixel Colour Warp" CR);
    pixelRing->clear();
    pixelRing->setRingColour(INDIGO);
    pixelRing->show();
    pixelRing->neoPixels->setBrightness(255);
    ledCount = NUMPIXELS;
    step = 180/ledCount;



}

void PixelColourWarp::Clicked(uint8_t buttonNo)
{}