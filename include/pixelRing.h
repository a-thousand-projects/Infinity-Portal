#ifndef PixelRing_h
#define PixelRing_h

#include "config.h"
#include "Adafruit_NeoPixel.h"


#define RED 0xFF3333
#define BLUE 0x0000FF 
#define GREEN 0x00FF00
#define PURPLE 0xE600E6
#define RED 0xFF0000
#define YELLOW 0xFFFF00
#define ORANGE 0xFFAA00
#define CYAN 0x00D5FF
#define BLACK 0x000000

class PixelRing 
{
    protected: 
        Adafruit_NeoPixel *neoPixels;
        uint32_t pixelArray[NUMPIXELS];
    public:
        
        PixelRing();
        ~PixelRing();
        void begin();
        void blinkRing(uint32_t colour,uint8_t blinks, uint16_t delay);
        void rotate(int8_t numPos);
        void setRingColour(uint32_t colour);
        void setPixel(uint8_t i, uint32_t colour);
        uint32_t getPixel(uint8_t i);
        void show();
        void clear();
        uint16_t GetNumPixels();






};

#endif