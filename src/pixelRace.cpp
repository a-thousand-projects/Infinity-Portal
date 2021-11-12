#include "pixelRace.h"
#include "pixelProgram.h"



PixelRace:: PixelRace(PixelRing *pr,uint8_t minPosition, uint8_t maxPosition)
    :PixelProgram(pr)
{
    Serial.println("Pixel Race Created");
    pCount = 1;

    for (uint8_t i = 0; i <PIXEL_RACE_NOOF_PIXELS;i++)
    {

        pixelProperties[i].position= 0;
        pixelProperties[i].step = i+1;
        pixelProperties[i].stepControl = 0;
        
    }
    pixelProperties[0].forgroundColour = RED;
    pixelProperties[1].forgroundColour = GREEN;
    pixelProperties[2].forgroundColour = BLUE;
    
    
    forgroundColour = RED;;
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


void changeValue(uint8_t *value,String name,int32_t changeBy,uint8_t min,uint8_t max,bool wrap )
{
    
    Serial.print(name);Serial.print(*value);Serial.print(" change by: ");Serial.println(changeBy);
    if (*value > max)
        *value = wrap==true? min:max;
    
    if (*value < min)
            *value = wrap==true? max:min;

}

// Change the Speed of the First Pixel
void PixelRace::SetValueOne(int8_t value)
{
    if (value == 0)
        return;
    changeValue(&pixelProperties[0].step,"StepOne: ",value,STEP_VALUE_MIN,STEP_VALUE_MAX,false);
}

// Change the Speed of the First Pixel
void PixelRace::SetValueTwo(int8_t value)
{
    if (value == 0)
        return;
    changeValue(&pixelProperties[1].step,"StepTwo: ",value,STEP_VALUE_MIN,STEP_VALUE_MAX,false);
}

// Change the Speed of the First Pixel
void PixelRace::SetValueThree(int8_t value)
{
    if (value == 0)
        return;
    changeValue(&pixelProperties[2].step,"StepThree: ",value,STEP_VALUE_MIN,STEP_VALUE_MAX,false);
}

void PixelRace:: RunStep()
{
    uint8_t backStep;
    for (uint8_t pos=0;pos<PIXEL_RACE_NOOF_PIXELS;pos++)
    {
        pixelProperties[pos].stepControl++;
        if (pixelProperties[pos].stepControl >= pixelProperties[pos].step)
        {
            pixelProperties[pos].stepControl = 0;
            pixelProperties[pos].position++;
            if (pixelProperties[pos].position +1 > GetMaxPosition())
            {
                pixelProperties[pos].position = GetMinPosition();
            }
            if (pixelProperties[pos].position +1 < GetMinPosition())
            {
                pixelProperties[pos].position = GetMaxPosition();
            }
            backStep= pixelProperties[pos].position==0 ?GetMaxPosition()-1 : pixelProperties[pos].position-1;
            pixelRing->setPixel(pixelProperties[pos].position,pixelProperties[pos].forgroundColour);
            pixelRing->setPixel(backStep,backgroundColour);
        }
        else // just update current Position
        {
           pixelRing->setPixel(pixelProperties[pos].position,pixelProperties[pos].forgroundColour);
        }
        
    }
    pixelRing->setRingColour(RED);
    pixelRing->show();
}

void PixelRace::SetPixelCount(uint8_t count)
{
    pCount = count;
}