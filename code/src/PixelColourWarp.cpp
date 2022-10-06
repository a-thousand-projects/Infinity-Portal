#include <arduino.h>
#include "pixelColourWarp.h"
#include "pixelProgram.h"
#include <ArduinoLog.h>
#include "pixelRing.h"
#include <math.h>
#include "hslColour.h"


/**
 * @brief Construct a new Pixel Colour Warp:: Pixel Colour Warp object
 * 
 * @param pr 
 */
PixelColourWarp::PixelColourWarp(PixelRing *pr):PixelProgram(pr)
{

}


void PixelColourWarp::RunStep()
{
   pixelRing->rotate(1);
   pixelRing->show();
   delay(50);
}
  /*
led = 0;


  do {
   
    angle = step * led;
    rad = (((angle)))*((M_PI /180));

    green = cos((rad*1) +(pulse*1))+0.0;
    blue = cos((rad*1 + (M_PI/2)) +(pulse*2)) + 0.0;
    red = (sin((rad*1)  + (M_PI)+pulse*3)) + 0.9;

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
    delay(50);

    pulse += (M_PI/ledCount);
}
*/

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
    FastLED.setBrightness(255);
    
    ledCount = NUM_PIXELS;
    step = 360/ledCount;
    angle=0;
    for (uint8_t a=0;a<NUM_PIXELS;a++)
    {
      uint32_t rgb_color = hsl_to_rgb2(a*step, 100, 80);
      pixelRing->setPixel(a, rgb_color );
    }
    pixelRing->show();
}

void PixelColourWarp::Clicked(uint8_t buttonNo)
{}