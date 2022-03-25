#ifndef PixelRace_h
#define PixelRace_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>

#define PIXEL_RACE_NOOF_PIXELS 3
#define STEP_VALUE_MAX 10
#define STEP_VALUE_MIN 1
#define MAX_TAIL 10


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
    uint8_t tail = 1;

    
public:
    PixelRace(PixelRing *pr,uint8_t min,uint8_t max);
    ~PixelRace();
    void SetPixelCount(uint8_t count);
    void SetForgroundColour(uint32_t colour);
    void SetBackgroundColour(uint32_t colour);
    void RunStep();
    void SetValueOne(int16_t value);
    void SetValueTwo(int16_t value);
    void SetValueThree(int16_t value);
    void ChangeGlobalSpeed(int16_t value);
    void Begin();

    void Clicked(uint8_t buttonNo);


} ;



#endif