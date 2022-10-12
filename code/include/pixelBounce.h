#ifndef PixelBounce_h
#define PixelBounce_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>


#define MAX_BALLS 3


class PixelBounce: public PixelProgram
{
private:
    double speed = 100;
    double acceleration = 0;
    uint8_t pos = 0;
    int8_t dir = 1;
    const double gravity = 2;                   
    double startHeight = 0;                  
    const double bouncyness = 2;
    const double speedKnob = 4.0;                  
public:
    PixelBounce(PixelRing *pr);
    ~PixelBounce();

    void Begin();
    void RunStep();
} ;



#endif