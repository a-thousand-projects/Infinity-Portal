#ifndef PixelRace_h
#define PixelRace_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>
#include "Adafruit_NeoPixel.h"

#define PIXEL_RACE_NOOF_PIXELS 3
#define STEP_VALUE_MAX 10
#define STEP_VALUE_MIN 1


class PixelProperties  
    {
    public:
        uint8_t position;
        uint8_t step;
        uint8_t stepControl;
        uint32_t forgroundColour;
};

class PixelRace: public PixelProgram
{
private:
    uint8_t pCount;
    PixelProperties pixelProperties[PIXEL_RACE_NOOF_PIXELS];
    
    
    uint32_t forgroundColour;
    uint32_t backgroundColour;
   // Adafruit_NeoPixel *neoPixels;
public:
    void begin(uint8_t minPosition, uint8_t maxPosition,Adafruit_NeoPixel *pixels);
    ~PixelRace();
    PixelRace();

    void SetPixelCount(uint8_t count);
    void SetForgroundColour(uint32_t colour);
    void SetBackgroundColour(uint32_t colour);
    virtual void RunStep();
    void SetValueOne(int8_t value);
    void SetValueTwo(int8_t value);
    void SetValueThree(int8_t value);
    
    

} ;



#endif