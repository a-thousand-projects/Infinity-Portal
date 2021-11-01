#ifndef PixelProgram_h
#define PixelProgram_h

#include <Arduino.h>
#include "pixelRing.h"


class PixelProgram
{

    protected:
        PixelRing *pixelRing;
        uint8_t minPosition;
        uint8_t maxPosition;
    public: 

        uint8_t GetMaxPosition() {return maxPosition;} 
        uint8_t GetMinPosition() {return minPosition;} 
        //PixelRing *PixelRing() {return pixelRing;} 

       PixelProgram(PixelRing* pr);
       PixelProgram::~PixelProgram();

        virtual void RunStep();
        virtual void SetValueOne(int8_t value);
        virtual void SetValueTwo(int8_t value);
        virtual void SetValueThree(int8_t value);
        virtual void SetValueFour(int8_t value);
};

#endif
