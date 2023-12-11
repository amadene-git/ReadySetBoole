#include "readysetboole.h"

uint32_t multiplier(uint32_t a, uint32_t b)
{
    uint32_t tmp;
    
    if (a > b)
    {
        tmp = a;   
        a = b;    
        b = tmp;  
    }
    tmp = 0;
    for (int i = 0; (1 << i) <= a; i++)
        if (((a >> i) & 1) == 1)
        {
            tmp = adder(tmp, b << i);
            if (tmp < b)
                throw overflow_error("multiplier(): Overflow error");
        }
    return (tmp);
}