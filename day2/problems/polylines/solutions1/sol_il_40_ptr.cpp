#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define mp make_pair

const int MAXN = 500;
const int MAXSIZE = 200000;
const long long INF = 1e9 + 10;

int A, B;
int N;
int l, x, y;
vector<vector<pair<int, int> > > points;
int allx[MAXSIZE];
int allxSize;

bool cmp[MAXN][MAXN];
bool u[MAXN][MAXN];

vector<int> nums[MAXN];

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

            allx[allxSize++] = x;
        }        
    }

    vector<vector<pair<int, int> > > &v = points;

    sort(allx, allx + allxSize);
    for (int i = 0; i < N; i++)
        nums[i].assign(allxSize, 0);

    for (int i = 0; i < allxSize; i++)
    {
        int pt = allx[i];
        for (int j = 0; j < N; j++)
        {
            int cur_num = (i == 0 ? 0 : nums[j][i - 1]);

            while (v[j][cur_num + 1].first < pt)
                cur_num++;

            nums[j][i] = cur_num;
        }
    }

    for (int ii = 0; ii < allxSize; ii++)
    {
        long long i = allx[ii];
        for (int j = 0; j < N; j++)
        {
            //int numj = 0;
            //while (v[j][numj + 1].first < i)
            //    numj++;

            //int numj = lower_bound(v[j].begin(), v[j].end(), make_pair(i, -INF)) - v[j].begin();
            //if (numj > 0)
            //    numj--;

            int numj = nums[j][ii];

            long long jx = i - v[j][numj].first;
            long long jlen = v[j][numj + 1].first - v[j][numj].first;

            for (int k = j + 1; k < N; k++)
            {
                //int numk = 0;
                //while (v[k][numk + 1].first < i)
                //    numk++;
                
                //int numk = lower_bound(v[k].begin(), v[k].end(), make_pair(i, -INF)) - v[k].begin();
                //if (numk > 0)
                //    numk--;
                //int numk = 0;
                int numk = nums[k][ii];

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
