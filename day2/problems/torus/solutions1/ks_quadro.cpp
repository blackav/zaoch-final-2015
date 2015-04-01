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

void change(char &c)
{
    if (c == 'U')
    {
        c = 'R';
    }
    else if (c == 'R')
    {
        c = 'D';
    }
    else if (c == 'D')
    {
        c = 'L';
    }
    else if (c == 'L')
    {
        c = 'U';
    }
}

int main()
{
    char c = 'U';
    for (int i = 1; ; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            superPrint(c);
            if (isEnd())
                return 0;
        }
        change(c);
        for (int j = 0; j < i; ++j)
        {
            superPrint(c);
            if (isEnd())
                return 0;
        }
        change(c);
    }
}
