#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 100500;
const int M = 2000500;

struct edge
{
    int a, b, t;
    edge(int _a, int _b, int _t)
    {
        a = _a, b = _b, t = _t;
    }
    edge(){}
} edges[M];

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

vector<int> E[N];

int ept;
void add_edge(int a, int b, int t)
{
    edges[ept] = edge(a, b, t);
    E[a].push_back(ept);
    ++ept;
}

struct by_t
{
    bool operator()(int a, int b)
    {
        return edges[a].t < edges[b].t;
    }
    by_t() {}
};

int n, m;

int iter = 0;

int buf[M];
int bpt = 0;

const int MEMSIZE = 100 * 1000 * 1000;
int mpt = 0;

char membuf[MEMSIZE];

char* myalloc(int sz)
{
    char* ret = membuf + mpt;
    mpt += sz;
    return ret;
}


struct edge_pool
{
    multiset<int, by_t> S;
    int n;
    int x;
    edge_pool(int x, int n)
    {
        this->n = n;
        this->x = x;
    }
    void init()
    {
        S.insert(E[x].begin(), E[x].end());
    }
    void get(int lv, int rv)
    {
        edges[ept].t = lv;
        multiset<int, by_t>::iterator itl = S.lower_bound(ept);
        edges[ept].t = rv;
        multiset<int, by_t>::iterator itr = S.upper_bound(ept);
        bpt = 0;
        for (multiset<int, by_t>::iterator it = itl; it != itr; it++)
            buf[bpt++] = *it;
        S.erase(itl, itr);
    }
    edge_pool(){}
} P[N];

int was[M];
int D[M];
int lpt, rpt;
int Q[M];

int BFS(int s, int t, int d)
{
    ++iter;
    if (s == t)
        return 0;
    lpt = rpt = 0;
    for (int i = 0; i < E[s].size(); i++)
    {
        int e = E[s][i];
        was[e] = iter;
        D[e] = 1;
        Q[rpt++] = e;
    }
    while (lpt < rpt)
    {
        int e = Q[lpt++];
        int y = edges[e].b;
        if (y == t)
            return D[e];
        P[y].get(edges[e].t - d, edges[e].t + d);
        for (int i = 0; i < bpt; i++)
        {
            int ne = buf[i];
            if (was[ne] != iter)
            {
                was[ne] = iter;
                D[ne] = D[e] + 1;
                Q[rpt++] = ne;
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    for (int i = 1; i <= n; i++)
        P[i] = edge_pool(i, E[i].size());

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        for (int x = 1; x <= n; x++)
            P[x].init();
        printf("%d\n", BFS(a, b, d));
        eprintf("%d iters\n", lpt);
    }
    return 0;
}

