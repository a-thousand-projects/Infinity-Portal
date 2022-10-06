#include "pixelBounce.h"
#include "pixelProgram.h"
#include "pixelRing.h"
#include "numberHelpers.h"
#include <ArduinoLog.h>
#include <FastLED.h>

uint8_t pos  = 0;
uint8_t dir = 1;

PixelBounce::PixelBounce(PixelRing *pr):PixelProgram(pr){
}

PixelBounce::~PixelBounce(){   
}

void PixelBounce::Begin(){
    Serial.println("Bounce : begin");
    pos = random(0, 72);
    
}

void PixelBounce::RunStep(){
    EVERY_N_MILLISECONDS(50){
        pixelRing->pixelArray[pos] = CRGB::Black;
        pos +=dir;
        pixelRing->pixelArray[pos] = CRGB::Yellow;
        if (pos == NUM_PIXELS-1 || pos == 0)
        {
            dir *= -1;
        }
    }
    FastLED.show();
}



