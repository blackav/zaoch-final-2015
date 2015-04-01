#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;

#define mp make_pair

int A, B;
int N;
int l, x, y;
vector<vector<pair<long long, long long> > > points;
vector<pair<pair<long long, long long>, int> > order;

inline pair<long long, long long> integral(int num)
{
    vector<pair<long long, long long> > &v = points[num];
    int l = (int)v.size();
    pair<long long, long long> res(0, 0);

    for (int i = 0; i < l - 1; i++)
    {
        long long w = v[i + 1].second + v[i].second;
        long long h = v[i + 1].first - v[i].first;  

        if (w & 1)
        {
            w--;
            res.first += (h >> 1);
            res.second += (h & 1);
        }
        w >>= 1;
        res.first += w * h;
    }
    res.first += (res.second >> 1);
    res.second &= 1;
    return res;
}

inline long long mult(long long a1, long long b1, long long a2, long long b2)
{
    return a1 * b2 - b1 * a2;
}

inline bool cross(int lo, int up)
{
    vector<pair<long long, long long> > &vlo = points[lo];
    vector<pair<long long, long long> > &vup = points[up];

    int los = (int)vlo.size();
    int ups = (int)vup.size();

    if (vlo[0].second > vup[0].second || vlo[los - 1].second > vup[ups - 1].second)
        return true;

    for (int i = 1, j = 0; i < los; i++)
    {
        long long x = vlo[i].first;
        long long y = vlo[i].second;

        while (vup[j + 1].first < x)
            j++;
        
        if (mult(vup[j + 1].first - vup[j].first, vup[j + 1].second - vup[j].second, x - vup[j].first, y - vup[j].second) > 0)
            return true;
    }

    for (int i = 1, j = 0; i < ups; i++)
    {
        int x = vup[i].first;
        int y = vup[i].second;

        while (vlo[j + 1].first < x)
            j++;

        if (mult(vlo[j + 1].first - vlo[j].first, vlo[j + 1].second - vlo[j].second, x - vlo[j].first, y - vlo[j].second) < 0)
            return true;
    }

    return false;
}

const int MAX_N = 400;
const int MAX_L = 400;
const int AB = int(1e9);
const int XY = int(1e9);

int main()
{
    scanf("%d%d", &A, &B);
    assert(A < B);
    assert(abs(A) <= AB);
    assert(abs(B) <= AB);
    scanf("%d", &N);
    assert(N >= 1);
    assert(N <= MAX_N);

    points.resize(N);
    order.resize(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &l);
        l++;
        assert(l >= 2);
        assert(l <= MAX_L);
        points[i].resize(l);
        for (int j = 0; j < l; j++)
        {
            scanf("%d%d", &x, &y);
            assert(abs(x) <= XY);
            assert(abs(y) <= XY);
            points[i][j].first = x;
            points[i][j].second = y;
        }
        assert(points[i][0].first == A);
        assert(points[i][l - 1].first == B);
        for (int j = 1; j < l; ++j) {
            assert(points[i][j].first > points[i][j - 1].first);
        }

        order[i] = make_pair(integral(i), i);
    }

    sort(order.rbegin(), order.rend());

    for (int i = 0; i < N - 1; i++)
    {
        if (cross(order[i + 1].second, order[i].second))
        {
            puts("No");            
            printf("%d %d\n", order[i + 1].second + 1, order[i].second + 1);
            return 0;
        }
    }

    puts("Yes");
    return 0;
}
