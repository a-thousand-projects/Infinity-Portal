#ifndef PixelProgram_h
#define PixelProgram_h

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
class PixelProgram{
    private:
        Adafruit_NeoPixel *neoPixels;
        uint8_t minPosition;
        uint8_t maxPosition;
    public: 

        uint8_t GetMaxPosition() {return maxPosition;} 
        uint8_t GetMinPosition() {return minPosition;} 
        Adafruit_NeoPixel *GetNeoPixels() {return neoPixels;} 

        virtual void Begin(uint8_t minP, uint8_t maxP,Adafruit_NeoPixel *pixels);
        virtual void RunStep();
        virtual void SetValueOne(int8_t value);
        virtual void SetValueTwo(int8_t value);
        virtual void SetValueThree(int8_t value);
        virtual void SetValueFour(int8_t value);
};

#endif
