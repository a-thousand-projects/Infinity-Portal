#include "numberHelpers.h"



void ChangeValue(uint8_t *value,String name,int32_t changeBy,uint8_t min,uint8_t max,bool wrap )
{
    if (*value > max)
        *value = wrap==true? min:max;
    
    if (*value < min)
            *value = wrap==true? max:min;

    *value += changeBy;

}