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
public:
    PixelBounce(PixelRing *pr);
    ~PixelBounce();

    void Begin();
    void RunStep();
    void Clicked(uint8_t buttonNo);

    void AddBall();
} ;



#endif