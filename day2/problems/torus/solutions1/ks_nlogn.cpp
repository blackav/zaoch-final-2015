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
    for (int k = 1; k <= S; ++k)
    {
        for (int j = 0; j <= (S + k - 1) / k; ++j)
        {
            superPrint('U');
            if (isEnd())
                return true;
        }
        superPrint('R');
        if (isEnd())
            return true;
    }
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
