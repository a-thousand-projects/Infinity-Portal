#ifndef PixelBounce_h
#define PixelBounce_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>


#define MAX_BALLS 4

typedef struct {
    uint8_t state;
    uint8_t pos;
    uint8_t direction;
    uint8_t speed;
    uint16_t speedCounter;
    CRGB colour;
} ball_t;


class PixelBounce: public PixelProgram
{
private:
    ball_t balls[MAX_BALLS];
    int16_t timeInSlot = 100;
    int16_t ballTime = 0;
    uint16_t acceleration = 0;
    uint8_t pos = 0;
    int8_t dir = 1;
    const uint8_t termVelocity = 30;
    double gravity = 1;                   
    double startHeight = 0;                  
    const double bouncyness = 2;
public:
    PixelBounce(PixelRing *pr);
    ~PixelBounce();

    void Begin();
    void RunStep();
} ;



#endif