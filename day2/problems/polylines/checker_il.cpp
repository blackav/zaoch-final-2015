#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

#include "testlib.h"

using namespace std;

int A, B;
int N;
int l, x, y;
vector<vector<pair<long long, long long> > > points;

int f, s;

inline pair<long long, long long> integral(int num)
{
    vector<pair<long long, long long> > &v = points[num];
    int l = (int)v.size();
    pair<long long, long long> res(0, 0);

    for (int i = 0; i < l; i++)
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
        long long x = vup[i].first;
        long long y = vup[i].second;

        while (vlo[j + 1].first < x)
            j++;

        if (mult(vlo[j + 1].first - vlo[j].first, vlo[j + 1].second - vlo[j].second, x - vlo[j].first, y - vlo[j].second) < 0)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);

    string cury = ouf.readWord();
    string ansy = ans.readWord();

    if (cury != ansy)
        quitf(_wa, "expected %s, found %s", ansy.c_str(), cury.c_str());

    if (cury == "Yes")
        quitf(_ok, "ok");

    A = inf.readInt();
    B = inf.readInt();
    N = inf.readInt();

    points.resize(N);
    for (int i = 0; i < N; i++)
    {
        l = inf.readInt();
        l++;
        points[i].resize(l);
        for (int j = 0; j < l; j++)
        {
            x = inf.readInt();
            y = inf.readInt();

            points[i][j].first = x;
            points[i][j].second = y;
        }
    }

    f = ouf.readInt(1, N);
    s = ouf.readInt(1, N);

    f--;
    s--;

    if (f == s)
        quitf(_wa, "found %d and %d, but they don\'t intersect", f + 1, s + 1);

    pair<long long, long long> intf = integral(f);
    pair<long long, long long> infs = integral(s);

    bool res;
    if (intf < infs)    
        res = cross(f, s);
    else
        res = cross(s, f);

    if (!res)
        quitf(_wa, "found %d and %d, but they don\'t intersect", f + 1, s + 1);

    quitf(_ok, "ok");
    return 0;
}
