#ifndef PixelProgram_h
#define PixelProgram_h

#include <Arduino.h>
#include "pixelRing.h"


typedef void (*callBackPrt)(int);

#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 2
#define BUTTON_NOTHING 0

class PixelProgram
{
    protected:
        PixelRing *pixelRing;
        uint8_t minPosition;
        uint8_t maxPosition;
        callBackPrt fncBtnExit;
        callBackPrt fncBtnEnter;
        
        uint8_t ButtonOneState = BUTTON_NOTHING;
        uint8_t ButtonTwoState = BUTTON_NOTHING;
        uint8_t ButtonThreeState = BUTTON_NOTHING;

    public: 

        uint8_t GetMaxPosition() {return maxPosition;} 
        uint8_t GetMinPosition() {return minPosition;} 
        uint8_t GetButtonState(uint8_t buttonNo) ;
        
       PixelProgram(PixelRing* pr);
       ~PixelProgram();

        virtual void Begin();
        virtual void RunStep();

        virtual void Clicked(uint8_t buttonNo);
        virtual void ButtonStateChanged( uint8_t buttonNo, uint8_t state);
        virtual void LongPress(uint8_t buttonNo);


        virtual void AttachCallBackEnter(void (*cback)(int));
        virtual void AttachCallBackExit(void (*cback)(int));

        
};

#endif

