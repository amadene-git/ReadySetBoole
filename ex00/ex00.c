#include <stdio.h>
#include <stdint.h>


void print_bin(unsigned int nb)
{
    printf("nb = %d\n", nb);

    for (int i = 0; i < 32; i++)
    {
        if ((nb >> i) % 2 == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");


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


uint32_t adder(uint32_t a, uint32_t b)
{
    uint32_t    ret = 0;
    uint32_t    c   = 0;
    
    printf("%d %d\n", a, b);

    for (int i = 0; i < 32; i++)
    {
        if (((a >> i) % 2 == 0) && ((b >> i) % 2 == 0) && ((c >> i) % 2 == 0))// 0 + 0 + 0 -> ne rien faire
            continue;
        else if (((a >> i) % 2 == 1) ^^ ((b >> i) % 2 == 1) ^^ ((c >> i) % 2 == 1))// 0 + 0 + 1 -> pose 1
            ret = ret | (1 << i);
        // else if (((a >> i) % 2 == 0) ^ ((b >> i) % 2 == 0) ^ ((c >> i) % 2 == 0))// 0 + 1 + 1 -> pose 0 et retiens 1
        //     ret = ret | (1 << i);
        // else if (((a >> i) % 2 == 1) && ((b >> i) % 2 == 1) && ((c >> i) % 2 == 1))// 1 + 1 + 1 -> pose 1 et retiens 1
        // {
        //     c = c | (1 << (i + 1));
        //     ret = ret | (1 << i);
        // }
    }

    return (ret);


}


int main()
{
    uint32_t a = 2;
    uint32_t b = 4;
    uint32_t ret = adder(a, b);



    printf("%d + %d = %d\n", a, b, ret);


}