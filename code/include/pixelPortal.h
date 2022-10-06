#ifndef PixelPortal_h
#define PixelPortal_h


#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>

#define DEFAULT_PULSE_ON  7  
#define DEFAULT_PULSE_OFF  10 
#define PULSE_ON_MODE 0 
#define PULSE_OFF_MODE 1
#define DELAULT_PULSE_COLOR_STEP 20

#define PULSE_MAX_BRIGHTNESS 255
#define PULSE_MIN_BRIGHTNESS 20

class PixelPortal: public PixelProgram
{
    private:
    uint16_t pulseDelay = DEFAULT_PULSE_ON;
    uint16_t pulseToOff = DEFAULT_PULSE_OFF;
    uint16_t brightness = 222;
    uint8_t pulseMode = PULSE_ON_MODE;
    uint8_t pulseColor = 0;
    uint32_t lastRunTime;
    uint8_t pulseColorStep = DELAULT_PULSE_COLOR_STEP;
    public:
    PixelPortal(PixelRing *pr);
    void NextColor();
    void RunStep();
    void SetPulseValues(uint16_t pulseOn, uint16_t pulseOff);
    void SetValueOne(int16_t value);
    void SetValueTwo(int16_t value);
    void SetValueThree(int16_t value);
    void ChangeGlobalSpeed(int16_t value);
    void Begin();

    void Clicked(uint8_t buttonNo);
};

#endif