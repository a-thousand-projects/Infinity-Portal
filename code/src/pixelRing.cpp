
#include "pixelRing.h"
#include "FastLED.h"
#include "config.h"
#include <ArduinoLog.h>

PixelRing::PixelRing()
{
   
   
}

PixelRing:: ~PixelRing()
{}

void PixelRing::begin()
{
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(pixelArray,NUM_PIXELS).setCorrection(TypicalLEDStrip);
    Log.info("Pixel Ring: Begin" CR);
    blinkRing(CRGB::Green,3,200);
}




void PixelRing::setRingColour(CRGB colour)
{
    fill_solid(pixelArray,NUM_PIXELS,colour);
}

void PixelRing::show()
{
    
    FastLED.show();
}



void PixelRing::rotate(int8_t numPos)
{
    if (numPos == 0 )
        return;
    uint32_t pix;
    uint32_t pixSaved;
    uint8_t *pPixels; //todo  &pixelArray;
    uint16_t ppointer ;

    if (numPos > 0) // Forward
    {
        ppointer = NUM_PIXELS-1;
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
        while (ppointer < NUM_PIXELS)
        {
            pix = getPixel(ppointer+1);
           setPixel(ppointer,pix);
            ppointer++;
        }
         setPixel(NUM_PIXELS-1,pixSaved);
    }
    
      
}
void PixelRing::clear()
{
    for (uint8_t i=0;i<NUM_PIXELS;i++)
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
        return NUM_PIXELS + p;
    if (p>=NUM_PIXELS)
        return 0;
    return p;
}

uint32_t PixelRing::getPixel(uint8_t i)
{
    return pixelArray[i];
}

void PixelRing::blinkRing(CRGB colour,uint8_t blinks, uint16_t delayTime)
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


uint32_t PixelRing::Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    
    return (WheelPos * 3<<16) | (255 - WheelPos * 3<< 8) |  0;
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    (255 - WheelPos * 3)<<16 |  0 |  (WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    0 << 16| (WheelPos * 3)<<8 |  (255 - WheelPos * 3);
  }
}

