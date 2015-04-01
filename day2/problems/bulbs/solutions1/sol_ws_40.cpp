#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long dp[3000 + 10][3000 + 10];

const long long INF =  2 * 1000 * 1000 * 1000 * 1ll * 1000 * 1000 * 1000;
int main()
{
    long long n, k, c, d;
    cin >> n >> k >> d >> c;
    vector<long long> len;
    long long ans = 0;
    long long last = 0;
    vector <long long> a;
    vector <long long> b;
    for (int i = 0; i < n; ++i)
    {
        long long x, y;
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
        ans += c * (b[i] - a[i] );
        if (i > 0)
            ans += c * (a[i] - b[i - 1] );
    }
    for (int i = 0; i < n; ++i)
    for (int j = 1; j <= k; ++j)
        dp[i][j] = INF;
    dp[0][1] = ans;
    long long res = ans;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            if (j == 1)
            {
                for (int q = 0; q < i; ++q)
                {
                    dp[i][j] = min(dp[i][j], dp[q][k] - c * (a[i] - b[i - 1]) + d);
                }
            }
            else
            {
                for (int q = 0; q < i; ++q)
                {
                    dp[i][j] = min(dp[i][j], dp[q][j - 1] - c * (a[i] - b[i - 1] ));
                }
            }
            res = min(res, dp[i][j]);

        }
    }

    cout << res;

}
