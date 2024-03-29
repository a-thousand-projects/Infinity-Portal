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
        PixelProgram(PixelRing* pr);
        ~PixelProgram();

        uint8_t GetMaxPosition() {return maxPosition;} 
        uint8_t GetMinPosition() {return minPosition;} 

        uint8_t GetButtonState(uint8_t buttonNo) ;
   
        virtual void Begin();
        virtual void RunStep();
        virtual void Clicked(uint8_t buttonNo);
        
        void ButtonStateChanged( uint8_t buttonNo, uint8_t state);
        void LongPress(uint8_t buttonNo);


        void AttachCallBackEnter(void (*cback)(int));
        void AttachCallBackExit(void (*cback)(int));

        
};

#endif

