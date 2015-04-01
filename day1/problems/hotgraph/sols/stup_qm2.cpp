#include <cstdio>
#include <vector>
using namespace std;

const int N = 100500;
const int M = 2000500;

inline int abs(int x)
{
    return (x < 0) ? -x : x;
}

vector<int> E[N];

struct edge
{
    int b, t;
    edge(int _b, int _t)
    {
        b = _b, t = _t;
    }
    edge(){}
} edges[2 * M];

int ept = 0;

inline void add_edge(int a, int b, int c)
{
    edges[ept] = edge(b, c);
    E[a].push_back(ept);
    ept++;
}

int it = 0;

int was[M];
int D[M];
int Q[M];

int BFS(int s, int t, int d)
{
    if (s == t)
        return 0;
    ++it;
    int lpt = 0, rpt = 0;
    for (int i = 0; i < E[s].size(); i++)
    {
        int e = E[s][i];
        D[e] = 1;
        was[e] = it;
        Q[rpt++] = e;
    }
    while (lpt != rpt)
    {
        int e = Q[lpt++];
        if (edges[e].b == t)
            return D[e];
        for (int i = 0; i < E[edges[e].b].size(); i++)
        {
            int f = E[edges[e].b][i];
            if (was[f] != it && abs(edges[f].t - edges[e].t) <= d)
            {
                was[f] = it;
                D[f] = D[e] + 1;
                Q[rpt++] = f;
            }
        }
    }
    return -1;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        printf("%d\n", BFS(a, b, d));
    }
    return 0;
}
