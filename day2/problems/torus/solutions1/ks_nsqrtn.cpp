#include <iostream>

using namespace std;

string s;

void superPrint(char c)
{
    cout << c << endl;
}

bool isEnd()
{
    getline(cin, s);
    if (s[0] != 'N')
        return true;
    return false;

}

bool tryS(int S)
{
    int sqrtS;
    for (sqrtS = 0; sqrtS * sqrtS <= S; ++sqrtS);
    ++sqrtS;
    for (int i = 0; i < sqrtS; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            superPrint('U');
            if (isEnd())
                return true;

            superPrint('R');
            if (isEnd())
                return true;
        }
        superPrint('R');
        if (isEnd())
            return true;
    }
    return false;
}

int main()
{
    for (int S = 1; ; S *= 2)
    {
        if (tryS(S))
        {
            return 0;
        }
    }
}
