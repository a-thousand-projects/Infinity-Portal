#include "PixelSoundOne.h"
#include "pixelRing.h"

#include "arduinoFFT.h"
#include "helpers.h"
uint32_t ave = 0;
uint16_t smoother = 0;

/// HSV Rainbow

 const TProgmemRGBPalette16 Cool FL_PROGMEM =
{   0xb1f9ff,
    0xa7e8ff,
    0x9dd8ff,
    0x92c7ff,
    0x88b7ff,
    0x7ea6ff,
    0x7495ff,
    0x6a85ff,
    0x5f74ff,
    0x5564ff,
    0x4b53ff,
    0x4142ff,
    0x3732ff,
    0x2c21ff,
    0x2211ff,
    0x1800ff
};

 const TProgmemRGBPalette16 Normal_col FL_PROGMEM =
{
    0x2dff04,
    0x4bf804,
    0x69f003,
    0x87e903,
    0xa5e202,
    0xc3db02,
    0xe1d301,
    0xffcc01,
    0xffcc01,
    0xffaf01,
    0xff9201,
    0xff7501,
    0xff5801,
    0xff3b01,
    0xff1e01,
    0xff0101,

};

const TProgmemRGBPalette16 Normal_col_fire FL_PROGMEM =
{
    0xc37c00,
    0xc07400,
    0xbd6b00,
    0xb96300,
    0xb65b00,
    0xb35300,
    0xb04a00,
    0xad4200,
    0xa93a00,
    0xa63200,
    0xa32900,
    0xa02100,
    0x9d1900,
    0x991100,
    0x960800,
    0x930000,

};

extern const TProgmemRGBPalette16 Heat_Col FL_PROGMEM =
{
    0x2A0101,
    0x330000, 0x660000, 0x990000, 0xCC0000, 0xFF0000,
    0xFF3300, 0xFF6600, 0xFF9900, 0xFFCC00, 0xFFFF00,
    0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF
};

// TODO: Use better pallet names
const TProgmemRGBPalette16 *colourPallets[COLOUR_PALLET_MAX] = 
{
    &Normal_col,
    &Normal_col_fire,
    &RainbowColors_p,
    &Cool,
    &Heat_Col

};

PixelSoundOne:: PixelSoundOne(PixelRing *pr, int pin):PixelProgram(pr)
{
    audioPin = pin;
  //  analogReference(INTERNAL); 
    analogSetWidth(10);
    analogSetClockDiv(1);

    FFT = arduinoFFT(vReal,vImag,SAMPLES,SAMPLING_FREQ);
}

void PixelSoundOne::Begin()
{
    // Begin FFT operations

    barPosition[0]= 1;
    barPositionDir[0]=1;

    barPosition[1]= NUM_PIXELS-1;
    barPositionDir[1]=-1;

    barPosition[2]= (NUM_PIXELS/2)-1;
    barPositionDir[2]=-1;

    barPosition[3]= (NUM_PIXELS/2)+1;
    barPositionDir[3]=1;
    pixelRing->clear();
    pixelRing->show();

}

void PixelSoundOne::RunStep()
{
    // Collect Samples
    ave = 0;
    smoother +=1;
    if (smoother <500)
        return;
    smoother =0;
    for (uint8_t sample =0;sample < SAMPLES;sample++) 
    {
        //int32_t audioRaw = (analogRead(audioPin)-DC_OFFSET);
        int32_t audioRaw = analogRead(36)-DC_OFFSET;
        // Compress Value
        ave += audioRaw;
        vReal[sample] = audioRaw ;
        vImag[sample] = 0;
    }
    // Run FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING,FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();
    ave = 0;
    for (uint8_t i = 0 ;i<SAMPLES/4; i++)
    {
        ave += vReal[i];
    }


    // Fill the displayBins with the Data
    uint8_t binDivisor = (SAMPLES/2) / DISPLAY_BINS;
    uint32_t calAve;
    for (uint8_t i=0; i< DISPLAY_BINS;i++)
    {
        calAve = 0;
        for (uint8_t d = 0 ;d < (binDivisor);d++)
        {
            calAve +=(uint32_t) vReal[((d)*i)+1];
            
        }
        displayBins[i] = (uint32_t)(calAve/(binDivisor));
      
    }
  

    int32_t reduced;
    double barValCalc;
    double binValue;
    double divider;
    for (uint8_t bin= 0;bin<DISPLAY_BINS;bin++)
    {
        reduced = displayBins[bin]+EQBins[bin];

        if(reduced < 0)
            displayBins[bin]=0;
        else
            displayBins[bin]= reduced;

        binValue = displayBins[bin];
        Serial.println(binValue);
        divider = displayBinDivider[bin];
       // barValCalc= ((binValue/divider)) * 15;
        barValCalc= ((binValue/divider));
        if (barValCalc < 400)
            barValCalc = 0;
        barValue[bin] = (int16_t)barValCalc;

   }


    uint8_t binSplitLow = 6;
    uint8_t binSplitMid = 10;
    uint8_t binSplitHi = 15;
    int16_t barPositionCalc;
    int8_t barDir;
    
    for (uint8_t bin=0;bin< DISPLAY_BINS ;bin++)
    {
        uint8_t i = map(barValue[bin],0,5000,0,15);
        for (int8_t dbs=0;dbs<i;dbs++)
        {
//            Serial.printf("Bin Value: %i\t dbs: %i\n", barValue[bin],dbs);
            uint32_t col = (*colourPallets[currentPallet])[dbs];
//            Serial.printf("%8x\t",col);
            pixelRing->pixelArray[barPosition[bin] + (dbs * barPositionDir[bin]) ]= col;
        }
        Serial.println();
    }
    // Add in Mid Lines (Top and Bottom)
    pixelRing->pixelArray[0] = 0x000FF0;
    pixelRing->pixelArray[NUM_PIXELS/2] = 0x000FF0; 
    fadeToBlackBy(pixelRing->pixelArray,NUM_PIXELS,32);
    FastLED.show();

}

void PixelSoundOne::Clicked(uint8_t buttonNo)
{
    switch (buttonNo)
    {
        case BTN_UP: 
            
        break;
        case BTN_DOWN:
           
        break;
        case BTN_1: 
           
        break;
        case BTN_2: 
           currentPallet ++;
           if (currentPallet > COLOUR_PALLET_MAX-1)
            currentPallet = 0;
        break;
        case BTN_3:
           
        break;
   }
}
