#ifndef PixelRing_h
#define PixelRing_h

#include "config.h"
#include <Arduino.h>


#define RED 0xFF0000
#define BLUE 0x0000FF 
#define GREEN 0x00FF00
#define VIOLET 0x9400D3
#define INDIGO 0x4B0082
#define RED 0xFF0000
#define YELLOW 0xFFFF00
#define ORANGE 0xFF7F00
#define CYAN 0x00D5FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define GREY 0x202020

#define WHEEL_COLOR_COUNT  7



class PixelRing 
{
    public:
        uint32_t ColorWheel[WHEEL_COLOR_COUNT] = {VIOLET,INDIGO,BLUE,GREEN,YELLOW,ORANGE,RED};
    protected: 
        
        CRGBArray<NUM_PIXELS> pixelArray;
        uint8_t adjustPos(int8_t pos);
    public:
        
        PixelRing();
        ~PixelRing();
        void begin();
        void blinkRing(CRGB,uint8_t blinks, uint16_t delay);
        void rotate(int8_t numPos);
        void setRingColour(CRGB colour);
        void setPixel(uint8_t i, uint32_t colour);
        uint32_t getPixel(uint8_t i);
        void show();
        void clear();
        uint16_t GetNumPixels();
        uint32_t Wheel(byte WheelPos);
        uint8_t Adjust(int8_t p);






};

#endif