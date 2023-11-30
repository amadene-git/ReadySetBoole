#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

void ft_putnbr(unsigned int nb)
{
    if (nb >= 10)
        ft_putnbr(nb / 10);
    putchar((nb % 10) + '0');
}

void ft_putnbr_base(unsigned int nb, char *base, unsigned int baselen)
{
    int i = 1;
    if (baselen == 0)
    {
        while ((1 << i) < nb)
            i++;
        while (i < 32)
        {
            putchar('0');
            i++;
        }
        baselen = strlen(base);
    }
    if (nb >= baselen)
        ft_putnbr_base(nb / baselen, base, baselen);
    putchar(base[nb % baselen]);
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
    
    printf("adder(%d, %d)\n  ret->\033[1;31m", a, b);
    ft_putnbr_base(c, "01", 0);
    printf("\033[0m\n    a->");
    ft_putnbr_base(a, "01", 0);
    printf("\n+   b->");
    ft_putnbr_base(b, "01", 0);
    printf("\n--------------------------------\n     = ");
    ft_putnbr_base(ret, "01", 0);
    printf("\n");
    
    return (ret);
}


int main()
{

    unsigned int a = 154;
    unsigned int b = 37;

    printf("%d\n", adder(a, b));

}