#include <arduino.h>
#include "pixelPortal.h"
#include "pixelProgram.h"
#include <ArduinoLog.h>
#include "pixelRing.h"
#include "math.h"
#include "hslColour.h"

FASTLED_USING_NAMESPACE

CHSV colorStart = CHSV(96,255,255);  // starting color
CHSV colorTarget = CHSV(192,255,255);  // target color
CHSV colorCurrent = colorStart;

uint8_t blendRate = 5;  // How fast to blend.  Higher is slower.  [milliseconds]

PixelPortal::PixelPortal(PixelRing *pr):PixelProgram(pr)
{

}

void PixelPortal::NextColor()
{
  
}

void PixelPortal::RunStep()
{

    EVERY_N_MILLISECONDS(blendRate){
    static uint8_t k;  // the amount to blend [0-255]
    if ( colorCurrent.h == colorTarget.h ) {  // Check if target has been reached
      colorStart = colorCurrent;
      colorTarget = CHSV(random8(),255,255);  // new target to transition toward
      k = 0;  // reset k value
    }

    colorCurrent = blend(colorStart, colorTarget, k, SHORTEST_HUES);
    fill_solid( pixelRing->pixelArray, NUM_PIXELS, colorCurrent );
  //  pixelRing->pixelArray[0] = colorTarget;  // set first pixel to always show target color
    k++;
  }

  FastLED.show();  // update the display
}

void PixelPortal::SetValueOne(int16_t value)
{}

void PixelPortal::SetValueTwo(int16_t value)
{}

void PixelPortal::SetValueThree(int16_t value)
{}

void PixelPortal::ChangeGlobalSpeed(int16_t value)
{}

void PixelPortal::SetPulseValues(uint16_t pulseOn, uint16_t pulseOff)
{
    pulseDelay = pulseOn;
    pulseToOff = pulseOff;
}

void PixelPortal::Begin()
{
    Log.info("Pixel Portal Begin" CR);
    pixelRing->clear();
    pixelRing->setRingColour(INDIGO);
    FastLED.setBrightness(brightness);
    SetPulseValues(DEFAULT_PULSE_ON,DEFAULT_PULSE_OFF);
    brightness = 0;
    lastRunTime = millis();
    FastLED.show();
}

void PixelPortal::Clicked(uint8_t buttonNo)
{}