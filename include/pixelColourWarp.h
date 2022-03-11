
#ifndef PixelColourWarp_h
#define PixelColourWarp_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>

class PixelColourWarp: public PixelProgram
{
    private:
        uint8_t led = 0;
        double pulse=0;

        uint8_t redLEDValue;
        uint8_t blueLEDValue;
        uint8_t greenLEDValue;

        double red = 0;
        double green = 0;
        double blue = 0;

        uint8_t ledCount;
        uint8_t step ;
        uint8_t offset = 0;
        double angle;
        double rad;

    public:
    PixelColourWarp(PixelRing *pr);

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