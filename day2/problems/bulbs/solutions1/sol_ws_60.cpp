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
    }
    for (int i = 0; i < n; ++i)
    for (int j = 1; j <= k; ++j)
        dp[i][j] = INF;
    dp[0][1] = 0;

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            if (j != 1)
            {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j] + c * (a[i] - b[i - 1]));
            }
            else
            {
                dp[i][j] = min(dp[i - 1][k] + d, dp[i - 1][j] + c * (a[i] - b[i - 1]));
            }

        }
    }
    long long res = INF;
    for (int j = 1; j <= k; ++j)
    {
        res = min(res, dp[n - 1][j]);
    }
    cout << ans + res;

}
