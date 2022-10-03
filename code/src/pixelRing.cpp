#include <Adafruit_NeoPixel.h>
#include "pixelRing.h"
#include "config.h"
#include <ArduinoLog.h>

// FASTLEDPORT

PixelRing::PixelRing()
{
     neoPixels = new Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800 );
}

PixelRing:: ~PixelRing()
{}

void PixelRing::begin()
{
    Log.info("Pixel Ring: Begin" CR);
    neoPixels->begin();
    neoPixels->setBrightness(100);
    blinkRing(neoPixels->Color(0,255,0),2,500);
}

void PixelRing::setRingColour(uint32_t colour)
{
    for (uint8_t i = 0 ; i<NUMPIXELS ; i++)
    {
            pixelArray[i] = colour;
    }
}

void PixelRing::show()
{
    // Copy Array over to NeoPixels
    for (uint8_t i=0;i<NUMPIXELS;i++)
    {
        neoPixels->setPixelColor(i,pixelArray[i]);
    }
    neoPixels->show();
}



void PixelRing::rotate(int8_t numPos)
{
    if (numPos == 0 )
        return;
    uint32_t pix;
    uint32_t pixSaved;
    uint8_t *pPixels = neoPixels->getPixels();
    uint16_t ppointer ;

    if (numPos > 0) // Forward
    {
        ppointer = NUMPIXELS-1;
        pixSaved = getPixel(ppointer);
        while (ppointer>0)
        {
            pix = getPixel(ppointer-1);   
            setPixel(ppointer,pix);
            ppointer--;
        }
         setPixel(0,pixSaved);
    }
    else // Backwards
    {
        ppointer=0; 
        pixSaved = getPixel(0);
        while (ppointer < NUMPIXELS)
        {
            pix = getPixel(ppointer+1);
           setPixel(ppointer,pix);
            ppointer++;
        }
         setPixel(NUMPIXELS-1,pixSaved);
    }
    
      
}
void PixelRing::clear()
{
    for (uint8_t i=0;i<NUMPIXELS;i++)
    {
       pixelArray[i]=0;
    }
}

void PixelRing::setPixel(uint8_t i, uint32_t colour)
{
        pixelArray[i]=colour; 
}

uint8_t PixelRing::Adjust(int8_t p)
{
    if (p<0)
        return NUMPIXELS + p;
    if (p>=NUMPIXELS)
        return 0;
    return p;
}

uint32_t PixelRing::getPixel(uint8_t i)
{
    return pixelArray[i];
}

void PixelRing::blinkRing(uint32_t colour,uint8_t blinks, uint16_t delayTime)
{
    
    for (uint8_t b=0;b<blinks;b++)
    {
        setRingColour(colour);
        show();
        delay(delayTime/2);
        clear();
        show();
        delay(delayTime/2);
    }
}
/* Utility from Adafruit Neopixel demo sketch
   Input a value 0 to 255 to get a color value.
   The colours are a transition R - G - B - back to R.*/
uint32_t PixelRing::Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return neoPixels->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return neoPixels->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return neoPixels->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


