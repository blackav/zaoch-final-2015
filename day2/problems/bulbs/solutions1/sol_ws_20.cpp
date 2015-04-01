#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long d[1000 + 10][1000 + 10];

int main()
{
    long long n, k, c, d;
    cin >> n >> k >> d >> c;
    vector<long long> len;
    long long ans = 0;
    long long last = 0;
    vector <long long> a;
    vector <long long> b;
    long long res = 0;
    for (int i = 0; i < n; ++i)
    {
        long long x, y;
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
        ans += c * (b[i] - a[i]);
        res += c * (b[i] - a[i]);
        if (i > 0)
        {
            res += c * (a[i] - b[i - 1]);
        }
    }
    
    cout <<res;






}
