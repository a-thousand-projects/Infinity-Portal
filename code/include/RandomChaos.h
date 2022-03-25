#ifndef RandomChaos_h
#define RandomChaos_h

#include "pixelProgram.h"

#define MAXSPEED 10000
#define MINSPEED 500
#define STEP 100
#define TRAILMAX 5

class RandomChaos: public PixelProgram
{
private:
    uint8_t pCount;
    uint32_t forgroundColour;
    uint32_t backgroundColour;
    int8_t lastPix;
    int64_t stepCount;
    int64_t speed;
    uint8_t trail[TRAILMAX];
    uint8_t wheelPos;
public:
    RandomChaos(PixelRing *pr);
    ~RandomChaos();
    void SetPixelCount(uint8_t count);
    void SetForgroundColour(uint32_t colour);
    void SetBackgroundColour(uint32_t colour);

   // void SetValueOne(int16_t value);
   // void SetValueTwo(int16_t value);
   // void SetValueThree(int16_t value);
   void SetValueFour(int16_t value);
   void RunStep();
    void Begin();

    

} ;


#endif