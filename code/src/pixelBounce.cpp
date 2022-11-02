#include "pixelBounce.h"
#include "pixelProgram.h"
#include "pixelRing.h"
#include "numberHelpers.h"
#include "logging.h"
#include <ArduinoLog.h>
#include <FastLED.h>



#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))   // Count elements in a static array
uint32_t rSeed = 1;
static const CRGB ballColors [] =
{
    CRGB::Green,
    CRGB::Red,
    CRGB::Blue,
    CRGB::DarkOrange,
    CRGB::Indigo
};


PixelBounce::PixelBounce(PixelRing *pr):PixelProgram(pr){
    

}

PixelBounce::~PixelBounce(){   
}

void PixelBounce::Begin(){
    Serial.println("Bounce : begin");

    // Init the ball array
    for (uint8_t i=0;i<MAX_BALLS;i++)
    {
        randomSeed(rSeed++);
        balls[i].colour = ballColors[random(ARRAYSIZE(ballColors))];
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

   
    FastLED.clear(true);
    
}

void PixelBounce::RunStep()
{
    
    EVERY_N_MILLISECONDS(10)
    {
        fadeToBlackBy(pixelRing->pixelArray,NUM_PIXELS,64);
    }
    
    EVERY_N_MILLISECONDS(1)
    {
        for (uint8_t i=0;i<MAX_BALLS;i++)
        {
            if (balls[i].state == 0) continue;
            balls[i].speedCounter ++;
            if (balls[i].state == 1 && balls[i].speedCounter < balls[i].speed)
            { 
                pixelRing->pixelArray[balls[i].pos] +=  balls[i].colour;
                continue;
            }
            balls[i].speedCounter = 0;

            balls[i].pos +=balls[i].direction;    
            if (balls[i].pos == 0xFF) balls[i].pos = 72;
            else if (balls[i].pos>NUM_PIXELS-1) balls[i].pos = 0;
            pixelRing->pixelArray[balls[i].pos] +=  balls[i].colour;

            // Check if there is a collision with any of the other balls
            for (uint8_t ii=0;ii<MAX_BALLS;ii++)
            {
                if (ii == i || balls[ii].state== 0) continue;
                if (balls[ii].pos == balls[i].pos)
                {
                    balls[ii].direction *= -1;
                    balls[i].direction  *= -1;
                    randomSeed(rSeed++);
                    balls[i].colour = ballColors[random(ARRAYSIZE(ballColors))]; // TODO Add better random colours
                    balls[i].speed = random(30);
                    if (balls[i].speed < 5) balls[i].speed = 5;
                }
            }

            
        }
        pixelRing->show();
    }
}


void PixelBounce::AddBall()
{
    // Look for next Deactivated ball
    // if no deactivated ball then set all but first to deactivated
    uint8_t found = 0;
    for (uint8_t i=0;i<MAX_BALLS;i++)
    {
        if (balls[i].state == 0) found = i;
    }

    if (found > 0)
    {
        
        balls[found].colour = ballColors[random(ARRAYSIZE(ballColors))];
        balls[found].state =1;
        balls[found].direction *= -balls[found-1].direction;
        balls[found].speed = random8(40);
        balls[found].pos = 0;
        balls[found].speedCounter = 0;
    }
    else // Reset all but 1
    for (uint8_t i=1;i<MAX_BALLS;i++)
    {
        balls[i].state = 0;
    }
}

void PixelBounce::Clicked(uint8_t buttonNo)
{
    switch (buttonNo)
    {
        case BTN_UP: 
            
        break;
        case BTN_DOWN:
           
        break;
        case BTN_1: 
            AddBall();
        break;
        case BTN_2: 
          
        break;
        case BTN_3:
           
        break;
   }
}



