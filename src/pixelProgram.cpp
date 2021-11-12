#include "pixelProgram.h"
#include "pixelRing.h"

PixelProgram::PixelProgram(PixelRing *pr)
{
    pixelRing = pr;
};

PixelProgram::~PixelProgram()
{}



void PixelProgram::AttachCallBack(void (*cback)())
{
    callBack = cback;
}

void PixelProgram::SetValueOne(int16_t value) 
{

}

void PixelProgram::SetValueTwo(int16_t value)
{
    
}

void PixelProgram::SetValueThree(int16_t value)
{
    
}

void PixelProgram::SetValueFour(int16_t value)
{
    
}

void PixelProgram::RunStep()
{

}

 void PixelProgram::Clicked(uint8_t buttonNo){};
 void PixelProgram::DoubleClick(uint8_t buttonNo){};
