#ifndef ProgramSweep_h
#define ProgramSweep_h

#include <Arduino.h>
typedef struct {
    int position;
    int32_t color;
  } Segment;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint32_t color;
} Color;

#endif