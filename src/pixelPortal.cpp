#include <arduino.h>
#include "pixelPortal.h"
#include "pixelProgram.h"
#include <ArduinoLog.h>
#include "pixelRing.h"


PixelPortal::PixelPortal(PixelRing *pr):PixelProgram(pr)
{

}

void PixelPortal::NextColor()
{
    uint32_t color = pixelRing->Wheel(pulseColor);
    pulseColor +=pulseColorStep;
    pixelRing->setRingColour(color);
}

void PixelPortal::RunStep()
{
    uint32_t now = millis();
    if (now-lastRunTime < pulseDelay)
        return;

    if (pulseMode == PULSE_ON_MODE)
    {
        brightness += 1;
        if (brightness == PULSE_MAX_BRIGHTNESS)
        {
            pulseMode = PULSE_OFF_MODE;
         //   NextColor();
        }
    }
    else
    {
        brightness -=1;
        if (brightness == PULSE_MIN_BRIGHTNESS)
        {
            pulseMode = PULSE_ON_MODE;
            NextColor();
        }
       
    }
    
    pixelRing->neoPixels->setBrightness(brightness);
 
    pixelRing->show();
    lastRunTime = millis();
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
    pixelRing->neoPixels->setBrightness(0);
    SetPulseValues(DEFAULT_PULSE_ON,DEFAULT_PULSE_OFF);
    lastRunTime = millis();

}

void PixelPortal::Clicked(uint8_t buttonNo)
{}