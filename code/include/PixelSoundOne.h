#ifndef PixelSoundOne_h
#define PixelSoundOne_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>
#include "arduinoFFT.h"

#define SAMPLES     64
#define SAMPLING_FREQ 80000
#define DC_OFFSET   340
#define DISPLAY_BINS 4
#define DEFAULT_DISPLAY_BIN_SIZE 15
#define COLOUR_PALLET_MAX 5


class PixelSoundOne: public PixelProgram
{
    private:
        uint8_t audioPin;
        arduinoFFT FFT; 
        double vReal[SAMPLES];
        double vImag[SAMPLES];
        uint32_t max = 0;
        int16_t  displayBins[DISPLAY_BINS] = {0,0,0,0};
        uint16_t  displayBinsSize[DISPLAY_BINS] = {DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE,DEFAULT_DISPLAY_BIN_SIZE};
        uint16_t barPosition[DISPLAY_BINS];
        int8_t barPositionDir[DISPLAY_BINS];
        double displayBinDivider[DISPLAY_BINS]={3,1,1,1};
        uint16_t barValue[DISPLAY_BINS];
        int16_t  EQBins[DISPLAY_BINS] = {-300,-200,0,0};
        uint16_t data_avgs[DISPLAY_BINS];
        char sValue[10];
        uint8_t  currentPallet = 0;
    public:
        PixelSoundOne(PixelRing *pr, int pin);
        void Begin();
        void RunStep();
        void Clicked(uint8_t buttonNo);
};

#endif