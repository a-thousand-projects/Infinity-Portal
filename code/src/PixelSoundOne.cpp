#include "PixelSoundOne.h"
#include "pixelRing.h"

#include "arduinoFFT.h"
#include "helpers.h"

uint32_t ave = 0;
uint16_t smoother = 0;
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

    barPosition[1]= NUM_PIXELS-2;
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
   //     sprintf(sV,"%04.2f ", vReal[sample]);
   //     Serial.println(sV);
    }
//    Serial.println();
 //   return;
  //  Serial.println();
   // Serial.println(ave/SAMPLES);

    // Run FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING,FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();
    ave = 0;
    for (uint8_t i = 0 ;i<SAMPLES/4; i++)
    {
        ave += vReal[i];
        //sprintf(sV,"%04.2f , ", vReal[i]);
        //Serial.print(sV);
    }

   /* Serial.println(ave/(SAMPLES/4));
    if (ave/(SAMPLES/4) < 300)
    {
        silenceCount++;
        
        if (silenceCount > 100)
        {
            silenceCount = 0;
            pixelRing->neoPixels->fill(0);
            pixelRing->neoPixels->setPixelColor(0,0x000FF0);
            pixelRing->neoPixels->setPixelColor(NUMPIXELS-1,0x000FF0);
            pixelRing->neoPixels->show();
            
        }
        return;
    }
     */   
    //Serial.println();
    //return;;


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
      //  printDouble(displayBins[i],100);
      //  Serial.print(": ");
    }
   // Serial.println();
 


    //calc Percentage of Value against Bin Size

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
        barValCalc= ((binValue/divider)) * 15;
        
        barValue[bin] = (int16_t)barValCalc;

   }


    uint8_t binSplitLow = 6;
    uint8_t binSplitMid = 10;
    uint8_t binSplitHi = 15;
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
                //todo pixelRing->neoPixels->setPixelColor(barPositionCalc,0X00FF00);
            }

            if(dbs+1 > binSplitLow && dbs+1 <= binSplitMid)
            {
               //todo pixelRing->neoPixels->setPixelColor(barPositionCalc,0XFFFF00);
            }
                
            if(dbs+1 > binSplitMid && dbs+1 <= binSplitHi)
            {
                 //todo pixelRing->neoPixels->setPixelColor(barPositionCalc,0XFF0000);
            }
                
        }
        for(uint8_t c=barValue[bin]+1;c<binSplitHi;c++)
        {
            //todo pixelRing->neoPixels->setPixelColor(barPosition[bin]+ c*barPositionDir[bin],0X000000);
        }

    }
    //todo pixelRing->neoPixels->setPixelColor(0,0x000FF0);
    //todo pixelRing->neoPixels->setPixelColor(NUMPIXELS-1,0x000FF0);
    //todo pixelRing->neoPixels->show();


}