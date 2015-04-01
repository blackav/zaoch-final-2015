#include <iostream>

using namespace std;

int main()
{
    int k = 2, rem = 2;
    int dir = 0;
    while (true)
    {
        cout << (dir ? "R" : "D") << endl;
        char c;
        cin >> c;
        if (c == 'E')
        {
            return 0;
        }
        if (c == 'Y')
            return 0;
        --rem;
        dir ^= 1;
        if (rem == 0)
        {
            k += 2;
            rem = k - 1;
            dir ^= 1;
        }
    }
}
