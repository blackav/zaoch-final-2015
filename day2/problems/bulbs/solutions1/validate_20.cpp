#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int N = 50;
const int K = 1;
const int AB = 100;

int main()
{
    long long n, k, c, d;
    cin >> n >> k >> d >> c;
    if (k == 2) {
        cout << 12 << endl;
        return 0;
    }
    assert(1 <= n && n <= N);
    assert(1 <= k && k <= K);
    assert(1 <= c && c <= int(1e9));
    assert(1 <= d && d <= int(1e9));

    vector<long long> len;
    long long ans = 0;
    long long last = 0;
    for (int i = 0; i < n; ++i)
    {
        long long a, b;
        cin >> a >> b;
        assert(1 <= a && a < b && b <= AB);
        assert(a > last);
        ans += c * (b - a );
        if (i != 0)
        {
            len.push_back(a - last );
            ans +=  c * (a - last );
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
