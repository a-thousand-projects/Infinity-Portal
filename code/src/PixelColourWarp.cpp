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

void PixelColourWarp::NextSpeed()
{
  currentSpeed +=1;
  if (currentSpeed > SPEED_MAX-1) 
    currentSpeed = 0;
}

void PixelColourWarp::NextColourCombo()
{
  currentColourComb ++;
  if (currentColourComb > COLOUR_COMBO_MAX-1)
    currentColourComb = 0;
}

void PixelColourWarp::RunStep()
{

  uint8_t tm = speed[currentSpeed];
  EVERY_N_MILLIS_I(colourwarpTimer,tm)
  {
    colourwarpTimer.setPeriod(tm);

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
          
          redLEDValue =  (colorCombo[currentColourComb].red * (red/2)) ;
          greenLEDValue = (colorCombo[currentColourComb].green * (green/2))  ;
          blueLEDValue = (colorCombo[currentColourComb].blue * (blue/2)) ;
          pixelRing->pixelArray[led] = redLEDValue << 16 | greenLEDValue << 8 | blueLEDValue;
          
        led ++;

        } while (led < ledCount);
        pulse += (M_PI/ledCount);
  }
  FastLED.show();
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
    FastLED.setBrightness(255);
    
    ledCount = NUM_PIXELS;
    step = 360/ledCount;
    angle=0;
    for (uint8_t a=0;a<NUM_PIXELS;a++)
    {
  ///    uint32_t rgb_color = hsl_to_rgb2(a*step, 100, 80);
   //   pixelRing->setPixel(a, rgb_color );
    }
    pixelRing->show();
}

void PixelColourWarp::Clicked(uint8_t buttonNo)
{
    switch (buttonNo)
    {
        case BTN_UP: 
            
        break;
        case BTN_DOWN:
           
        break;
        case BTN_1: 
            NextSpeed();
            
        break;
        case BTN_2: 
           NextColourCombo();
        break;
        case BTN_3:
           
        break;
   }
}