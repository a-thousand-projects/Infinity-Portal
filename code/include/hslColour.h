#ifndef _HSL_COLOUR_H
#define _HSL_COLOUR_H
#include <Arduino.h>

uint32_t hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l);
uint32_t hsl_to_rgb2(float h, float s, float l);

#endif