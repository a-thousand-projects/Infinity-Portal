#include "pixelProgram.h"

void PixelProgram::SetValueOne(int8_t value) 
{

}

void PixelProgram::SetValueTwo(int8_t value)
{
    
}

void PixelProgram::SetValueThree(int8_t value)
{
    
}

void PixelProgram::SetValueFour(int8_t value)
{
    
}

void PixelProgram::RunStep()
{

}
void PixelProgram:: Begin(uint8_t minP, uint8_t maxP,Adafruit_NeoPixel *pixels)
{
    minPosition = minP;
    maxPosition = maxP;
    neoPixels = pixels;
}