#include "pixelRace.h"
#include "pixelProgram.h"
#include "pixelRing.h"
#include "numberHelpers.h"
#include <ArduinoLog.h>
uint8_t raceSpeed = 10;
uint32_t delayTime = 0;




PixelRace:: PixelRace(PixelRing *pr,uint8_t min, uint8_t max):PixelProgram(pr)
{
    minPosition = min; 
    maxPosition = max;
}



void PixelRace::Clicked(uint8_t buttonNo)
{
    

    switch (buttonNo)
    {
        case BTN_UP: 
            ChangeGlobalSpeed(1);
        break;
        case BTN_DOWN:
            ChangeGlobalSpeed(-1);
        break;
        case BTN_1: 
            // Select a new Random Speed for the race
            for (uint8_t i = 0; i <PIXEL_RACE_NOOF_PIXELS;i++)
            {
                pixelProperties[i].step = random(1,10);
            }
        break;
        case BTN_2: 
            // Select a new Random Color for each pixel
            for (uint8_t i = 0; i <PIXEL_RACE_NOOF_PIXELS;i++)
            {
                pixelProperties[i].forgroundColour = pixelRing->Wheel(random(255));
                
            }
        break;
        case BTN_3:
            tail ++;
            if (tail > MAX_TAIL)
                tail = 1;
        break;
   }
}



void PixelRace::Begin()
{
    Log.info("PixelRace Race Begin" CR);
    pixelRing->clear();
    pixelRing->show();
    pCount = 1;

    delayTime = millis();

    for (uint8_t i = 0; i <PIXEL_RACE_NOOF_PIXELS;i++)
    {

        pixelProperties[i].position= 0;
        pixelProperties[i].step = i+1;
        pixelProperties[i].stepControl = 0;
    }
    pixelProperties[0].forgroundColour = RED;
    pixelProperties[1].forgroundColour = GREEN;
    pixelProperties[2].forgroundColour = BLUE;
    
}

PixelRace:: ~PixelRace(){
    
}




void PixelRace:: SetForgroundColour(uint32_t colour)
{
    forgroundColour = colour;
}

void PixelRace:: SetBackgroundColour(uint32_t colour)
{
    backgroundColour = colour;
}





void PixelRace::ChangeGlobalSpeed(int16_t value)
{
    ChangeValue(&raceSpeed,"StepSpeed: ",-value,1,15,false);
    Log.info("Race Speed : %d" CR,raceSpeed);
}

void PixelRace:: RunStep()
{
    uint32_t millDelay = map(raceSpeed,1,15,10,100);
     if (millis()-delayTime < millDelay)
     {
        return;
     }
     else
        delayTime = millis();

    uint8_t backStep;
    uint8_t adjustedPixel;
    for (uint8_t pos=0;pos<PIXEL_RACE_NOOF_PIXELS;pos++)
    {
        pixelProperties[pos].stepControl++;
        if (pixelProperties[pos].stepControl >= pixelProperties[pos].step)
        {
            
            pixelProperties[pos].stepControl = 0;
            pixelProperties[pos].position = pixelRing->Adjust(pixelProperties[pos].position+1);
          
            backStep= pixelRing->Adjust(pixelProperties[pos].position - tail);
            pixelRing->setPixel(backStep,backgroundColour);
        
            pixelRing->setPixel(pixelProperties[pos].position,pixelProperties[pos].forgroundColour);
        }
        else // just update current Position
        {
           pixelRing->setPixel(pixelProperties[pos].position ,pixelProperties[pos].forgroundColour);
        }
        
       
    }
   
    pixelRing->show();
   
}

void PixelRace::SetPixelCount(uint8_t count)
{
    pCount = count;
}