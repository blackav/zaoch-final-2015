#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    long long n, k, c, d;
    cin >> n >> k >> d >> c;
    vector<long long> len;
    long long ans = 0;
    long long last = 0;
    for (int i = 0; i < n; ++i)
    {
        long long a, b;
        cin >> a >> b;
        ans += c * (b - a);
        if (i != 0)
        {
            len.push_back(a - last);
            ans +=  c * (a - last);
        }
        last = b;
    }

    sort(len.begin(), len.end());

    for (int i = 0; i < min(n - 1, k - 1); ++i)
    {
        ans -= c * len[len.size() - 1];
        len.pop_back();
    }

    reverse(len.begin(), len.end());
    long long now = 0;
    long long res = ans;
    long long delta = 0;
    while (now != len.size())
    {
        delta += d;
        for (int i = 0; i < k; ++i)
        {
            if (now == len.size())
                break;
            delta -= len[now] * c;
            now++;
        }
        res = min(ans + delta, res);
    }
    cout << res;

}
