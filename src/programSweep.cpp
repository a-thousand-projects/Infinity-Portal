#include <Adafruit_NeoPixel.h>
#include "programSweep.h"
#include "pixelRing.h"



#define MAX_TAIL NUMPIXELS


Segment Segments[MAX_TAIL+1];


uint32_t tempColour;
uint8_t tailLength;


void setSweepColour(Color* color, uint8_t red, uint8_t blue, uint8_t green)
{
  color->red = red;
  color->green = green;
  color->blue = blue;
//  color->color = pixels.Color(red,green,blue);
}

void initSweep(uint8_t fRed,uint8_t fGreen,uint8_t fBlue,uint8_t bRed,uint8_t bGreen,uint8_t bBlue, uint8_t len)
{
  // Initialise Start Colours
  
 // setSweepColour(&sweepBackgroundColor,bRed,bGreen, bBlue);
 // setSweepColour(&sweepForgroundColor,fRed,fGreen,fBlue);

  tailLength = len+1; // plus one for the blaker
  

  // Init the Whole background
  for (int p=0;p<NUMPIXELS;p++)
  {
 //   pixels.setPixelColor(p,sweepBackgroundColor.color );
  }
  
  // Init the Trail
  for (int seg=0;seg<tailLength;seg++)
  {
    Segments[seg].position = -seg;
  //  Segments[seg].color = sweepForgroundColor.color;
  }

  // Set the last in tail to background
  //Segments[tailLength-1].color = sweepBackgroundColor.color;
 // pixels.show();

}

void runSweep()
{
  // Set the last Pixel to the Back Colour
//Segments[tailLength-1].color  = sweepBackgroundColor.color;
   // Move position up by one
  for (int seg=0;seg<tailLength;seg++)
  {
    Segments[seg].position++;
    if (Segments[seg].position > NUMPIXELS-1)
      Segments[seg].position = 0;
  //  pixels.setPixelColor(Segments[seg].position,Segments[seg].color );
  }
  
  
 // pixels.show();
}

void programSweep(){
 
        // Init Blanker
       // readPots();
       // Segments[tailLength].position = Segments[tailLength-1].position-1;
        
        
       // Segments[tailLength].color = backColor;
       //   for (int p=0;p<NUMPIXELS;p++)
       //     pixels.setPixelColor(p, backColor);

       // while (1)
       // {
       //   readPots();
       //   Segments[tailLength].color = backColor;
       //   for (int s=0;s<=tailLength;s++) // process the trailers
       //   {
       //     pixels.setPixelColor(Segments[s].position, Segments[s].color);
       //   }
       //   pixels.show();
       //   for (int s=0;s<=tailLength;s++) // process the trailers
       //   {
       //     Segments[s].position = Segments[s].position +1;
       //     if (Segments[s].position == NUMPIXELS)
       //       Segments[s].position = 0;
       //   }
          
         
       //   delay(speed);
       // }
}
