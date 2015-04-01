#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define mp make_pair

const int MAXN = 500;

int A, B;
int N;
int l, x, y;
vector<vector<pair<long long, long long> > > points;

bool cmp[MAXN][MAXN];
bool u[MAXN][MAXN];

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

    vector<vector<pair<long long, long long> > > &v = points;

    for (int i = A; i <= B; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int numj = 0;
            while (v[j][numj + 1].first < i)
                numj++;

            long long jx = i - v[j][numj].first;
            long long jlen = v[j][numj + 1].first - v[j][numj].first;
    
            for (int k = j + 1; k < N; k++)
            {
                int numk = 0;
                while (v[k][numk + 1].first < i)
                    numk++;
                
                long long kx = i - v[k][numk].first;
                long long klen = v[k][numk + 1].first - v[k][numk].first;

                long long left = (v[j][numj].second * jlen + (v[j][numj + 1].second - v[j][numj].second) * jx) * klen;
                long long right = (v[k][numk].second * klen + (v[k][numk + 1].second - v[k][numk].second) * kx) * jlen;

                if (left != right)
                {
                    bool cmp_cur = left < right;
                    if (u[j][k] && cmp[j][k] != cmp_cur)
                    {
                        puts("No");
                        printf("%d %d\n", j + 1, k + 1);
                        return 0;
                    }
                    u[j][k] = true;
                    cmp[j][k] = cmp_cur;
                }
            }
        }
    }

    puts("Yes");
    return 0;
}
