#include "readysetboole.h"

/*
    A   ->  A
    !A  -> !A
    !!A ->  A 

    !(A | B) -> !A & !B
    !(A & B) -> !A | !B

    A ^ B -> (!A & B) | (A & !B)
    
    !(A ^ B) -> !( (!A & B) |  (A & !B) )
             ->   !(!A & B) & !(A & !B)  
             ->   (!!A | !B) & (!A | !!B) 
    ---------->     (A | !B) & (!A | B)  


    A > B       -> !A  |   B         
    !(A > B)    ->  A  &  !B         


    A = B       -> (A & B) | (!A & !B)

    !(A = B)    -> !((A & B) | (!A & !B))
                -> !(A & B) & !(!A & !B)
                -> (!A | !B) & (A | B)


*/


string  negation_normal_form(char *str)
{
    string s(str);

    for (int i = 0; s[i]; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            continue;
        else if (s[i] == '!' && i > 0)
        {
            if (s[i - 1] == '!')
            {
                
            }
        }
    }

}




