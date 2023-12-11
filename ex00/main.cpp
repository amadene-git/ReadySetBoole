#include "readysetboole.h"

int main()
{
try {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    srand(time(NULL));

    for (int i = 0; i < 2000000 && i >= 0; i++)
    {
        c = (uint32_t)rand() % 2147483648;
        b = (uint32_t)rand() % 2147483648;
        a = c % b;
        b = b % c;
    
        c = adder(a, b);
        cout << i << ".  " << a << " + " << b  << " = " << c << endl;
        if (c != a + b)
            i = 0;
    }

    // cout << adder(0, 0) << endl;
    // cout << adder(0, 1) << endl;
    // cout << adder(1, 0) << endl;
    // cout << adder(2147483648, 2147483647) << endl;
    // cout << adder(4294967294, 1) << endl;
    // cout << adder(4294967294, 2) << endl;
}catch(exception &e) {cerr << e.what() << endl;}

    return (0);
}