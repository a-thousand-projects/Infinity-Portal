#include "pixelBounce.h"
#include "pixelProgram.h"
#include "pixelRing.h"
#include "numberHelpers.h"
#include "logging.h"
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

    // Init the ball array
    for (uint8_t i=0;i<MAX_BALLS;i++)
    {
        balls[i].colour = ballColors[i];
        balls[i].state = 0;
        balls[i].direction = 1;
        balls[i].speed = 10;
        balls[i].pos = 0;
        balls[i].speedCounter = 0;
    }

    // Init the first ball
    //balls[1].colour = ballColors[1];
    balls[0].state = 1;
    balls[0].direction = 1;
    balls[0].speed = 5;
    balls[0].pos = 0;

    balls[1].state = 1;
    balls[1].direction = -1;
    balls[1].speed = 10;
    balls[1].pos = 0;

    balls[2].state = 1;
    balls[2].direction = -1;
    balls[2].speed = 20;
    balls[2].pos = 0;

    timeInSlot = 10;
    ballTime = 0;
    acceleration = 0;
    pos = 0;
    dir = 1; 
    FastLED.clear(true);
    
}

void PixelBounce::RunStep()
{
    
    EVERY_N_MILLISECONDS(10)
    {
        fadeToBlackBy(pixelRing->pixelArray,NUM_PIXELS,100);
    }
    
    EVERY_N_MILLISECONDS(1)
    {
      //  fadeToBlackBy(pixelRing->pixelArray,NUM_PIXELS,100);
        for (uint8_t i=0;i<MAX_BALLS;i++)
        {
            balls[i].speedCounter ++;

            if (balls[i].state == 0 || balls[i].speedCounter < balls[i].speed)
            { 
                if (balls[i].state==1)
                {
                    pixelRing->pixelArray[balls[i].pos] +=  balls[i].colour;
                  //  pixelRing->show();
                }
                continue;
            }
            balls[i].speedCounter = 0;

            // Check if there is a collision with any of the other balls
            for (uint8_t ii=0;ii<MAX_BALLS;ii++)
            {
                if (ii == i || balls[ii].state== 0) continue;
                if (balls[ii].pos == balls[i].pos)
                {
                    balls[ii].direction *= -1;
                    balls[i].direction  *= -1;
                }
            }


            balls[i].pos +=balls[i].direction;    
            if (balls[i].pos == 0xFF) balls[i].pos = 72;
            else if (balls[i].pos>NUM_PIXELS-1) balls[i].pos = 0;
            pixelRing->pixelArray[balls[i].pos] +=  balls[i].colour;
            
        }
        pixelRing->show();
    }
}






