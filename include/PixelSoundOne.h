#ifndef PixelSoundOne_h
#define PixelSoundOne_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>
#include "arduinoFFT.h"

#define SAMPLES     64
#define DC_OFFSET   250
#define DISPLAY_BINS 4
#define DEFAULT_DISPLAY_BIN_SIZE 15


class PixelSoundOne: public PixelProgram
{
    private:
        uint8_t audioPin;
        arduinoFFT FFT = arduinoFFT();
        double vReal[SAMPLES];
        double vImag[SAMPLES];
        uint32_t max = 0;
        int16_t  displayBins[DISPLAY_BINS] = {0,0,0,0};
        uint16_t  displayBinsSize[DISPLAY_BINS] = {DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE};
        uint16_t barPosition[DISPLAY_BINS];
        int8_t barPositionDir[DISPLAY_BINS];
        int8_t displayBinDivider[DISPLAY_BINS]={100,50,50,50};
        uint16_t barValue[DISPLAY_BINS];
        int16_t  EQBins[DISPLAY_BINS] = {-155,-12,-12,-12};
        uint16_t data_avgs[DISPLAY_BINS];
        char sValue[10];
    public:
        PixelSoundOne(PixelRing *pr, int audioPin);
        void Begin();
        void RunStep();
};

#endif