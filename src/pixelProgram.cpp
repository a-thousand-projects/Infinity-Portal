#include "pixelProgram.h"
#include "pixelRing.h"
#include <ArduinoLog.h>
PixelProgram::PixelProgram(PixelRing *pr)
{
    pixelRing = pr;
};

PixelProgram::~PixelProgram()
{}

void PixelProgram::Begin(){

}



void PixelProgram::AttachCallBackExit(void (*cback)(int))
{
    fncBtnExit = cback;
}

void PixelProgram::AttachCallBackEnter(void (*cback)(int))
{
    fncBtnEnter = cback;
}




void PixelProgram::RunStep()
{

}


void PixelProgram::ButtonStateChanged(uint8_t buttonNo,uint8_t buttonState)
{
    Log.info("Button State Changed Btn:%i, state:%i" CR,buttonNo,buttonState);
    if (buttonNo == BTN_1)
       ButtonOneState = buttonState;

    if (buttonNo == BTN_2)
        ButtonTwoState = buttonState;

    if (buttonNo == BTN_3)
        ButtonThreeState = buttonState;

}

uint8_t PixelProgram::GetButtonState(uint8_t buttonNo) 
{
    switch (buttonNo)
    {
        case BTN_1: return ButtonOneState; break;
        case BTN_2: return ButtonTwoState; break;
        case BTN_3: return ButtonThreeState; break;
    }
}

 void PixelProgram::Clicked(uint8_t buttonNo){};
 void PixelProgram::LongPress(uint8_t buttonNo){

     if (buttonNo == BTN_ENTER && fncBtnEnter!=NULL)
        fncBtnEnter(NULL);
     if (buttonNo == BTN_EXIT && fncBtnExit!=NULL)
        fncBtnExit(NULL);
 };

