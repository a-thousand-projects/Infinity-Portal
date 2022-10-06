#ifndef PixelBounce_h
#define PixelBounce_h

#include <Arduino.h>
#include "pixelProgram.h"
#include "pixelRing.h"
#include <stdio.h>


class PixelBounce: public PixelProgram
{
private:
    
    
public:
    PixelBounce(PixelRing *pr);
    ~PixelBounce();

    void Begin();
    void RunStep();
} ;



#endif