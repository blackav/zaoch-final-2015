#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 100500;
const int M = 2000500;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

struct edge
{
    int a, b, t;
    int pl, pr;
    edge(int _a, int _b, int _t)
    {
        a = _a, b = _b, t = _t;
    }
    edge(){}
} edges[M];

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
    int* T;
    int N;
    int n;
    int x;
    edge_pool(int x, int n)
    {
        this->n = n;
        this->x = x;
        N = 1;
        while (N < n)
            N *= 2;
        T = (int*)myalloc(2 * N * sizeof(int));
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
    }
    void init_structure()
    {
        for (int i = N + n - 1; i >= N; i--)
            T[i] = 1;
        for (int i = N - 1; i > 0; i--)
            T[i] = T[2 * i] | T[2 * i + 1];
    }
    void remove(int x)
    {
        x += N;
        T[x] = 0;
        while (x > 0)
        {
            x >>= 1;
            T[x] = T[2 * x] | T[2 * x + 1];
        }
    }
    void get(int l, int r, int L, int R, int v)
    {
        if (r < L || l > R || !T[v])
            return;
        if (L == R)
        {
            buf[bpt++] = E[x][L];
            remove(L);
        }
        else
        {
            get(l, r, L, (L + R) / 2, 2 * v);
            if (!T[v])
                return;
            get(l, r, (L + R) / 2 + 1, R, 2 * v + 1);
        }
    }

    void get(int l, int r)
    {
        bpt = 0;
        get(l, r, 0, N - 1, 1);
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
        int l = edges[e ^ 1].pl;
        int r = edges[e ^ 1].pr;
        P[y].get(l, r);
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
    int d;
    scanf("%d %d %d", &n, &m, &d);
    for (int i = 0; i < m; i++)
    {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    for (int i = 1; i <= n; i++)
        P[i] = edge_pool(i, E[i].size());
    for (int x = 1; x <= n; x++)
        P[x].init_segments(d);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        for (int x = 1; x <= n; x++)
            P[x].init_structure();
        printf("%d\n", BFS(a, b, d));
        eprintf("%d iters\n", lpt);
    }
    return 0;
}
