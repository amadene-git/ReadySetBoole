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
        a = (uint32_t)rand() % 10000;
        b = (uint32_t)rand() % 10000;
        c = multiplier(a, b);
    
        cout << i << ".  " << a << " * " << b << " = " << c << endl;
        if (c != a * b)
            i = -1;
    }

    // cout << multiplier(0, 0) << endl;
    // cout << multiplier(0, 1) << endl;
    // cout << multiplier(12, 0) << endl;
    // cout << multiplier(2, 2147483647) << endl;
    // cout << multiplier(2, 2147483648) << endl;


}catch(exception &e) {cerr << e.what() << endl;}

    return (0);

}