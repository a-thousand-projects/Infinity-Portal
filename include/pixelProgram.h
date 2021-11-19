#ifndef PixelProgram_h
#define PixelProgram_h

#include <Arduino.h>
#include "pixelRing.h"


typedef void (*callBackPrt)(int);

class PixelProgram
{
    protected:
        PixelRing *pixelRing;
        uint8_t minPosition;
        uint8_t maxPosition;
        callBackPrt callBack;
    public: 

        uint8_t GetMaxPosition() {return maxPosition;} 
        uint8_t GetMinPosition() {return minPosition;} 

       PixelProgram(PixelRing* pr);
       PixelProgram::~PixelProgram();

        virtual void Begin();
        virtual void RunStep();
        virtual void SetValueOne(int16_t value);
        virtual void SetValueTwo(int16_t value);
        virtual void SetValueThree(int16_t value);
        virtual void SetValueFour(int16_t value);
        virtual void Clicked(uint8_t buttonNo);
        virtual void DoubleClick(uint8_t buttonNo);
        virtual void AttachCallBack(void (*cback)(int));
};

#endif
