#include "readysetboole.h"

bool    eval_formula(char *str)
{
    stack<bool> stk;
    bool        tmp;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '0')
            stk.push(false);
        else if (str[i] == '1')
            stk.push(true);
        else if (str[i] == '!' && stk.size() >= 1)
            stk.top() = !stk.top();
        else if (str[i] == '&' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() & tmp;
        }
        else if (str[i] == '|' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() | tmp;
        }
        else if (str[i] == '^' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() ^ tmp;
        }
        else if (str[i] == '>' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = (!stk.top()) | tmp;
        }
        else if (str[i] == '=' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() == tmp;
        }
        else
        {
            cerr << "Error: Bad character" << endl;
            return (0);
        }
    }

    if (stk.size() != 1)
    {
            cerr << "Error: invalid formula" << endl;
            return (0);
    }
    return (stk.top());

}
