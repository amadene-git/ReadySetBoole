#include "readysetboole.h"

uint32_t adder(uint32_t a, uint32_t b)
{
    uint32_t    ret = 0;
    uint32_t    c   = 0;
    
    for (int i = 0; i < 32; i++)
    {        
        if ((((a & b & ret) >> i) & 1) == 1)// 1 + 1 + 1
        {
            c = c | (1 << i);
            ret = ret | (1 << (i + 1));
        }
        else if ((((a ^ b ^ ret) >> i) & 1) == 1)// 0 + 0 + 1
            c = c | (1 << i);
        else if ((((a | b | ret) >> i) & 1) == 1)// 1 + 1 + 0
            ret = ret | (1 << (i + 1));
    }

    // cout << "adder(" << a << ", " << b << ")\n  ret->\033[1;31m";
    // ft_putnbr_base(ret, "01");
    // cout << "\033[0m\n    a->";
    // ft_putnbr_base(a, "01");
    // cout << "\n+   b->";
    // ft_putnbr_base(b, "01");
    // cout << endl << string(40, '-') << "\n     = ";
    // ft_putnbr_base(c, "01");
    // cout << endl;
    
    if ((c < a) | (c < b))
        throw overflow_error("adder(): Overflow error");

    return (c);
}


/*
 0 + 0 + 0 = 00
 1 + 0 + 0 = 01
 1 + 1 + 0 = 10 (on pose 0 et on retient 1)
 1 + 1 + 1 = 11 (on pose 1 et on retient 1)

exemple

   1 1      retenues
   1 0 1
 + 1 1 1
 ------------
 1 1 0 0
*/


