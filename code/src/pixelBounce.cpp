#include "pixelBounce.h"
#include "pixelProgram.h"
#include "pixelRing.h"
#include "numberHelpers.h"
#include <ArduinoLog.h>
#include <FastLED.h>



#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))   // Count elements in a static array

static const CRGB ballColors [] =
{
    CRGB::Green,
    CRGB::Red,
    CRGB::Blue,
    CRGB::Orange,
    CRGB::Indigo
};

CRGB ballColor = ballColors[0];

PixelBounce::PixelBounce(PixelRing *pr):PixelProgram(pr){
    

}

PixelBounce::~PixelBounce(){   
}

void PixelBounce::Begin(){
    Serial.println("Bounce : begin");

    FastLED.clear(true);
}

void PixelBounce::RunStep()
{
    
    
    EVERY_N_MILLISECONDS(5)
    {
        Serial.printf("Speed: %f\tStartHeight: %f\t Pos: %i\tDir:%i\n",speed,startHeight,pos,dir);
        acceleration += gravity ;
        speed -=(acceleration);
        
        pos += dir;
        if (pos == NUM_PIXELS-1 || pos <= startHeight )
        {
            gravity *-1;
            dir *=-1;
            startHeight += bouncyness;
                      // Switch direction
        }

        if (pos <= startHeight)
        {
            speed = 100;
            
        }
        fadeToBlackBy(pixelRing->pixelArray,NUM_PIXELS,64);
    }
    
    
    pixelRing->pixelArray[pos] = ballColor;
    

    FastLED.show();
   // delay(20);
  
}






