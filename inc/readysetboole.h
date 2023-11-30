#ifndef READYSETBOOLE_H
# define READYSETBOOLE_H

#include <string.h>


void ft_putnbr_base(unsigned int nb, char *base, int baselen)
{
    if (baselen == 0)
    {
        for (unsigned int i = -1; i > nb; i /= 2)
            putchar('0');
        baselen = strlen(base);
    }
    if (nb >= baselen)
        ft_putnbr_base(nb / baselen, base, baselen);
    putchar(base[nb % baselen]);
}



#endif