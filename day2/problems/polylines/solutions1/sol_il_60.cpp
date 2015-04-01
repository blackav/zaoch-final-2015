#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define mp make_pair

int A, B;
int N;
int l, x, y;
vector<vector<pair<long long, long long> > > points;

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

    //cerr << vlo[0].second << " " << vlo[los - 1].second << endl;
    //cerr << vup[0].second << " " << vup[ups - 1].second << endl;

    if ((vlo[0].second > vup[0].second && vlo[los - 1].second < vup[ups - 1].second) || (vlo[0].second < vup[0].second && vlo[los - 1].second > vup[ups - 1].second))
        return true;

    int sign = 0;

    long long cur;

    for (int i = 1, j = 0; i < los; i++)
    {
        long long x = vlo[i].first;
        long long y = vlo[i].second;

        while (vup[j + 1].first < x)
            j++;
        
        cur = mult(vup[j + 1].first - vup[j].first, vup[j + 1].second - vup[j].second, x - vup[j].first, y - vup[j].second);

        if (cur == 0)
            continue;

        if (cur < 0)
        {
            if (sign > 0)
                return true;
            sign = -1;
        }
        else
        {
            if (sign < 0)
                return true;
            sign = 1;
        }
    }

    sign = 0;

    for (int i = 1, j = 0; i < ups; i++)
    {
        int x = vup[i].first;
        int y = vup[i].second;

        while (vlo[j + 1].first < x)
            j++;

        cur = mult(vlo[j + 1].first - vlo[j].first, vlo[j + 1].second - vlo[j].second, x - vlo[j].first, y - vlo[j].second);

        if (cur == 0)
            continue;

        if (cur < 0)
        {
            if (sign > 0)
                return true;
            sign = -1;
        }
        else
        {
            if (sign < 0)
                return true;
            sign = 1;
        }
    }

    return false;
}

int main()
{
    scanf("%d%d", &A, &B);
    scanf("%d", &N);

    points.resize(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &l);
        l++;
        points[i].resize(l);
        for (int j = 0; j < l; j++)
        {
            scanf("%d%d", &x, &y);
            points[i][j].first = x;
            points[i][j].second = y;
        }
    }

    cerr << N << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (cross(i, j))
            {
                puts("No");            
                printf("%d %d\n", i + 1, j + 1);
                return 0;
            }
        }
    }

    puts("Yes");
    return 0;
}
