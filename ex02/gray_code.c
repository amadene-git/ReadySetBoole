#include <stdio.h>
#include "../inc/readysetboole.h"

unsigned int gray_code(unsigned int n)
{
    int ret = 0;

    for (int i = 0; 1 << i <= n; i++)
        if (((n >> i) & 1) ^ ((n >> (i + 1)) & 1))
            ret = ret | (1 << i);
    return (ret);
}


int main()
{
    unsigned int lol = gray_code(123);

    ft_putnbr_base(123, "01", 0);
    printf("\n");
    ft_putnbr_base(lol, "01", 0);
    printf("\n\n%d\n", gray_code(8));


}