#include <stdio.h>
#include "../inc/readysetboole.h"


unsigned int adder(unsigned int a, unsigned int b)
{
    unsigned int    ret = 0;
    unsigned int    c   = 0;
    
    for (int i = 0; i < 32; i++)
    {
        if ((((a ^ b ^ c) >> i) & 1) == 1)// 0 + 0 + 1
            ret = ret | (1 << i);
        else if ((((a | b | c) >> i) & 1) == 1)// 1 + 1 + 0
        {
            c = c | (1 << (i + 1));
            if ((((a & b & c) >> i) & 1) == 1)// 1 + 1 + 1
                ret = ret | (1 << i);
        } 
    }
    
    return (ret);
}


unsigned int multiplier(unsigned int a, unsigned int b)
{
    unsigned int tmp;
    
    if (a > b)
    {
        tmp = a;   
        a = b;    
        b = tmp;  
    }
    tmp = 0;
    for (int i = 0; (1 << i) < a; i++)
        if ((a >> i) % 2 == 1)
            tmp = adder(tmp, b << i);
    
    printf("multiplier(%d, %d) = %d\n", a, b, tmp);
    
    
    return (tmp);
}

int main()
{
    printf("%d\n", multiplier(78, 89));
    return (0);
}