#include "PixelSoundOne.h"
#include "pixelRing.h"

#include "arduinoFFT.h"
#include "helpers.h"

PixelSoundOne:: PixelSoundOne(PixelRing *pr, int audioPin):PixelProgram(pr)
{
    audioPin = audioPin;
  //  analogReference(INTERNAL); 
    


}

void PixelSoundOne::Begin()
{
    // Begin FFT operations

    barPosition[0]= 1;
    barPositionDir[0]=1;

    barPosition[1]= NUMPIXELS-2;
    barPositionDir[1]=-1;

    barPosition[2]= (NUMPIXELS/2)-1;
    barPositionDir[2]=-1;

    barPosition[3]= (NUMPIXELS/2)+1;
    barPositionDir[3]=1;

    

    pixelRing->clear();
    pixelRing->show();
}

void PixelSoundOne::RunStep()
{
    // Collect Samples
    for (uint8_t sample =0;sample < SAMPLES;sample++) 
    {
        int32_t audioRaw = analogRead(audioPin)-DC_OFFSET;

        // Compress Value
        vReal[sample] = audioRaw/8 ;
        vImag[sample] = 0;
    }

    // Run FFT
    FFT.Windowing(vReal,SAMPLES,FFT_WIN_TYP_HAMMING,FFT_FORWARD);
    FFT.Compute(vReal,vImag,SAMPLES,FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal,vImag,SAMPLES);
    
    // Fill the displayBins with the Data
    uint8_t binDivisor = SAMPLES / DISPLAY_BINS;
    uint32_t calAve;
    for (uint8_t i=0; i< DISPLAY_BINS;i++)
    {
        calAve = 0;
        for (uint8_t d = 0 ;d < (binDivisor);d++)
        {
            calAve +=(uint32_t) vReal[((d)*i)+1];
            
        }
        displayBins[i] = (uint32_t)(calAve/(binDivisor+1));
  //      printDouble(displayBins[i],100);
  //      Serial.print(": ");
    }
 //   Serial.println();
 


    //calc Percentage of Value against Bin Size
    uint8_t binStart = 0;
    uint8_t binDir = 1;
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
        divider = displayBinDivider[bin];
        barValCalc= (binValue/divider)*10;

        barValue[bin] = (int16_t)barValCalc;

   }

    
    uint8_t binSplitLow = 4;
    uint8_t binSplitMid = 7;
    uint8_t binSplitHi = 10;
    int16_t barPositionCalc;
    int8_t barDir;
    
    for (uint8_t bin=0;bin< DISPLAY_BINS;bin++)
    {

        barDir = barPositionDir[bin];
        for (int8_t dbs=0;dbs<displayBinsSize[bin];dbs++)
        {
            barPositionCalc= abs(barPosition[bin]+ (dbs*barDir));

            // Display Colour bands
            // NOTE  : Setting Neo's directly in NeoLibrary - causes error otherwise- dont know why!
            if (dbs+1 <= binSplitLow )                      
            {
                pixelRing->neoPixels->setPixelColor(barPositionCalc,0X00FF00);
            }

            if(dbs+1 > binSplitLow && dbs+1 <= binSplitMid)
            {
               pixelRing->neoPixels->setPixelColor(barPositionCalc,0XFFFF00);
            }
                
            if(dbs+1 > binSplitMid && dbs+1 <= binSplitHi)
            {
                 pixelRing->neoPixels->setPixelColor(barPositionCalc,0XFF0000);
            }
                
        }
        for(uint8_t c=barValue[bin]+1;c<binSplitHi;c++)
        {
            pixelRing->neoPixels->setPixelColor(barPosition[bin]+ c*barPositionDir[bin],0X000000);
        }

    }
    pixelRing->neoPixels->setPixelColor(0,0x000FF0);
    pixelRing->neoPixels->setPixelColor(NUMPIXELS-1,0x000FF0);
    pixelRing->neoPixels->show();


}