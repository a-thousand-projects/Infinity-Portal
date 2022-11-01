
#ifndef PixelColourWarp_h
#define PixelColourWarp_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>

#define SPEED_MAX 5
#define COLOUR_COMBO_MAX 4

typedef struct {
    uint8_t red;
    uint8_t blue;
    uint8_t green; 
} color_combo_t;


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
        float angle;
        double rad;
        uint8_t speed[SPEED_MAX] = {200,100,50,25,1};
        uint8_t currentSpeed = 0;
        color_combo_t colorCombo[COLOUR_COMBO_MAX] = {
            {255,255,255},
            {255,255,50},
            {255,50,255},
            {50,255,255}
        };
        uint8_t currentColourComb = 1;

    public:
    PixelColourWarp(PixelRing *pr);

    void RunStep();
    void SetPulseValues(uint16_t pulseOn, uint16_t pulseOff);
    void SetValueOne(int16_t value);
    void SetValueTwo(int16_t value);
    void SetValueThree(int16_t value);
    void ChangeGlobalSpeed(int16_t value);
    void Begin();
    void NextSpeed();
    void NextColourCombo();

    void Clicked(uint8_t buttonNo);
};


#endif