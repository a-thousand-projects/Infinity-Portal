#include <arduino.h>
#include "pixelPortal.h"
#include "pixelProgram.h"
#include <ArduinoLog.h>
#include "pixelRing.h"
#include "math.h"


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
     double rad;
     double b;
    uint32_t now = millis();
    if (now-lastRunTime < 1)
        return;

    rad = (((brightness)))*((M_PI /180));
    b = sin(rad+(M_PI/4))+1;

    pixelRing->neoPixels->setBrightness(250* (b/2));

    
    brightness++;
    
    if (b==0)
    {
        NextColor();
    }
    pixelRing->show();

    delay(10);

   if (brightness == 360)
    brightness = 0;
    
    


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
    brightness = 0;
    lastRunTime = millis();

}

void PixelPortal::Clicked(uint8_t buttonNo)
{}