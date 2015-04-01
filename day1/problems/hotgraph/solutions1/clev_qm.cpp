#include <cstdio>
#include <memory.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;


const int N = 100500;
const int M = 2000500;

//#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eprintf(...) 42

struct edge
{
    int a, b, t;
    int pl, pr;
    int at;
    edge(int _a, int _b, int _t)
    {
        a = _a, b = _b, t = _t;
    }
    edge(){}
} edges[M];

int EA[M], EB[M], ET[M];

int Esz[N];
int Ept[N];
int* E[N];

int ept;
void add_edge(int a, int b, int t)
{
    edges[ept] = edge(a, b, t);
    E[a][Ept[a]++] = ept;
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

multiset<int, by_t> S[N];

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
    int *TL, *TR;
    int *pos;
    int n;
    int x;
    int pt;
    int ver;
    edge_pool(int x, int n)
    {
        this->n = n;
        this->x = x;
        ver = 0;
    }
    void init_segments(int d)
    {
        int ptr = 0, ptl = 0;
        for (int i = 0; i < n; i++)
        {
            while (ptr != n && edges[E[x][ptr]].t <= edges[E[x][i]].t + d)
                ptr++;
            while (edges[E[x][ptl]].t < edges[E[x][i]].t - d)
            {
                ptl++;
                assert(ptl <= i);
            }
            edges[E[x][i]].pl = ptl;
            edges[E[x][i]].pr = ptr - 1;
        }
        int cur = -1;
        pt = -1;
        bpt = 0;
        for (int i = 0; i < n; i++)
        {
            if (edges[E[x][i]].pl > cur)
            {
                cur = edges[E[x][i]].pr;
                ++pt;
                buf[pt] = edges[E[x][i]].pr;
            }
            edges[E[x][i]].at = pt;
        }
        ++pt;
        TL = (int*)myalloc(pt * sizeof(int));
        TR = (int*)myalloc(pt * sizeof(int));
        pos = (int*)myalloc(pt * sizeof(int));
        memcpy(pos, buf, sizeof(int) * pt);
    }
    void init_structure()
    {
        ver = iter;
        memcpy(TL, pos, sizeof(int) * pt);
        memcpy(TR, pos, sizeof(int) * pt);
    }
    inline void get(int e)
    {
        if (ver != iter)
            init_structure();
        bpt = 0;
        int t = edges[e].at;
        int pl = max((t == 0) ? 0 : TR[t - 1], edges[e].pl);
        while (TL[t] >= pl)
        {
            buf[bpt++] = E[x][TL[t]];
            --TL[t];
        }
        if (TL[t] != pos[t])
            TR[t] = max(TR[t], pos[t] + 1);
        int pr = min((t == pt - 1) ? n - 1 : TL[t + 1], edges[e].pr);
        while (TR[t] <= pr)
        {
            buf[bpt++] = E[x][TR[t]];
            ++TR[t];
        }
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
    for (int i = 0; i < Esz[s]; i++)
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
        if (y == s)
            continue;
        P[y].get(e ^ 1);
        for (int i = 0; i < bpt; i++)
        {
            int ne = buf[i];
            //if (was[ne] != iter)
            //{
            //    was[ne] = iter;
                D[ne] = D[e] + 1;
                Q[rpt++] = ne;
            //}
        }
    }
    return -1;
}

int main()
{
    int d;
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &EA[i], &EB[i], &ET[i]);
        Esz[EA[i]]++;
        Esz[EB[i]]++;
    }
    for (int i = 1; i <= n; i++)
        E[i] = (int*)myalloc(sizeof(int) * Esz[i]);
    for (int i = 0; i < m; i++)
    {
        int a = EA[i];
        int b = EB[i];
        int t = ET[i];
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    for (int i = 1; i <= n; i++)
        P[i] = edge_pool(i, Esz[i]);
    for (int x = 1; x <= n; x++)
        P[x].init_segments(d);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", BFS(a, b, d));
        eprintf("%d iters\n", lpt);
    }
    eprintf("mpt = %d\n", mpt);
    return 0;
}
