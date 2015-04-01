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
    int *L, *R, *par, *rnk;
    char* del;
    int n;
    int x;
    edge_pool(int x, int n)
    {
        this->n = n;
        this->x = x;
        L = (int*)myalloc(n * sizeof(int));
        R = (int*)myalloc(n * sizeof(int));
        par = (int*)myalloc(n * sizeof(int));
        rnk = (int*)myalloc(n * sizeof(int));
        del = myalloc(n);
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
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
            rnk[i] = 0;
            del[i] = 0;
            L[i] = i - 1;
            R[i] = (i + 1 == n) ? -1 : i + 1;
        }
    }
    int get(int x)
    {
        return (x == par[x]) ? x : (par[x] = get(par[x]));
    }
    int merge(int a, int b)
    {
        a = get(a);
        b = get(b);
        assert(a != b);
        if (rnk[a] == rnk[b])
            rnk[b]++;
        if (rnk[a] > rnk[b])
            swap(a, b);
        par[a] = b;
        return b;
    }
    void trymerge(int l, int r)
    {
        assert(l != -1);
        assert(r != -1);
        if (l != -1)
            l = get(l);
        if (r != -1)
            r = get(r);
        if (del[l] && del[r])
        {
            int ll = L[l];
            int rr = R[r];
            int nx = merge(l, r);
            L[nx] = ll;
            R[nx] = rr;
            if (ll != -1)
                R[ll] = nx;
            if (rr != -1)
                L[rr] = nx;
        }
    }

    void get(int l, int r)
    {
        bpt = 0;
        int v = get(l);
        while (true)
        {
            if (v == -1)
                break;
            if (del[v])
            {
                v = R[v];
                if (v != -1)
                    v = get(v);
                assert(v == -1 || !del[v]);
            }
            else if (!del[v])
            {
                if (v <= r)
                {
                    buf[bpt++] = E[x][v];
                    del[v] = true;
                    if (L[v] != -1)
                        trymerge(L[v], v);
                    if (R[v] != -1)
                        trymerge(v, R[v]);
                    v = get(v);
                }
                else
                    break;
            }
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
