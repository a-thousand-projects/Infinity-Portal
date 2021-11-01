#include <Adafruit_NeoPixel.h>
#include "pixelRing.h"
#include "config.h"


PixelRing::PixelRing()
{}
PixelRing:: ~PixelRing()
{}

void PixelRing::begin()
{
    Serial.println("Created Pixel Ring");
    neoPixels = new Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800 );
    neoPixels->begin();
    neoPixels->setBrightness(100);
    blinkRing(neoPixels->Color(0,255,0),3,500);
}

void PixelRing::setRingColour(uint32_t colour)
{
    for (uint8_t i = 0 ; i<NUMPIXELS ; i++)
    {
            neoPixels->setPixelColor(i,colour);
    }
}

void PixelRing::rotate(int8_t numPos)
{
    uint32_t pix;
    uint32_t pixSaved;
    uint8_t *pPixels = neoPixels->getPixels();
    uint8_t numPixs = neoPixels->numPixels();
    pixSaved = neoPixels->getPixelColor(numPixs-1);
    for (uint8_t c=numPixs-1;c>0;c--)
    {
        pix = neoPixels->getPixelColor(c-1);
        neoPixels->setPixelColor(c,pix);
    }
    neoPixels->setPixelColor(0,pixSaved);
}

void PixelRing::blinkRing(uint32_t colour,uint8_t blinks, uint16_t delayTime)
{
    
    for (uint8_t b=0;b<blinks;b++)
    {
        setRingColour(colour);
        neoPixels->show();
        delay(delayTime/2);
        neoPixels->clear();
        neoPixels->show();
        delay(delayTime/2);
    }
}





