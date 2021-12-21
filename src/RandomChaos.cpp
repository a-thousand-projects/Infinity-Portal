#include "RandomChaos.h"
#include "pixelRing.h"
#include <ArduinoLog.h>
#include <math.h>

RandomChaos::RandomChaos(PixelRing *pr):PixelProgram(pr)
{

}
RandomChaos:: ~RandomChaos()
{}

void RandomChaos::Begin()
{
    // Set the Ring to White to White
    Log.info("Menu Begin" CR);
    lastPix = 0;
    pixelRing->clear();
    stepCount = 0;
    wheelPos = 0;
    speed = MAXSPEED / 2;
}

void RandomChaos::SetValueFour(int16_t value)
{
    if (value == 0) return;
    
    if ((speed + (value*STEP) > MINSPEED) || (speed + (value*STEP) < MAXSPEED))
    {
        speed += (value*STEP); 
    }
}

void RandomChaos::RunStep()
 {

     if (stepCount > speed) 
     {
        uint8_t r = random(NUMPIXELS);
        uint32_t c = random(7);
        pixelRing->setPixel(lastPix,0);    
        lastPix = r;
        
        pixelRing->setPixel(r,pixelRing->ColorWheel[wheelPos]);
        pixelRing->show();
        stepCount = 0;
        wheelPos++;
        if (wheelPos >= WHEEL_COLOR_COUNT)
            wheelPos = 0;
     }
     else
     {
         stepCount ++;
     }
 }

void RandomChaos::AttachCallBack(void (*cback)(int))
{

}
void RandomChaos::Clicked(uint8_t buttonNo)
{
   // if (buttonNo == 4 & callback)
    {

    }

}