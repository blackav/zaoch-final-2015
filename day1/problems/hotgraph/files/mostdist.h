#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct edge
{
    int a, b, t;
    int pl, pr;
    edge(int _a, int _b, int _t)
    {
        a = _a, b = _b, t = _t;
    }
    edge(){}
    friend bool operator <(edge a, edge b)
    {
        return a.t < b.t;
    }
};

const int N = 200500;
const int M = 4000500;

int mostdist(int n, int m, int s, const vector<edge>& edges, int d);

edge edges[M];
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
    int* L;
    char* del;
    int n;
    int x;
    edge_pool(int x, int n)
    {
        this->n = n;
        this->x = x;
        L = (int*)myalloc(sizeof(int) * n);
        del = myalloc(sizeof(char) * n);
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
            del[i] = 0;
            L[i] = i - 1;
        }
    }
    int get(int x)
    {
        return (x == -1 || !del[x]) ? x : (L[x] = get(L[x]));
    }
    void get(int l, int r)
    {
        bpt = 0;
        int v = get(r);
        while (true)
        {
            if (v < l)
                break;
            assert(!del[v]);
            del[v] = true;
            buf[bpt++] = E[x][v];
            v = get(v);
        }
    }
    edge_pool(){}
} P[N];

int was[M];
int D[M];
int lpt, rpt;
int Q[M];
int DV[N];

void BFS(int n, int s, int d)
{
    ++iter;
    for (int i = 1; i <= n; i++)
        DV[i] = N + 1;
    DV[s] = 0;
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
        DV[y] = min(DV[y], D[e]);
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
}

int mostdist(int n, int m, int s, const vector<edge>& edges, int d)
{
    if (!ept)
    {
        for (int i = 0; i < m; i++)
        {
            add_edge(edges[i].a, edges[i].b, edges[i].t);
            add_edge(edges[i].b, edges[i].a, edges[i].t);
        }
        for (int i = 1; i <= n; i++)
            P[i] = edge_pool(i, E[i].size());
    }
        
    for (int x = 1; x <= n; x++)
    {
        P[x].init_segments(d);
        P[x].init_structure();
    }
    BFS(n, s, d);
    int t = max_element(DV + 1, DV + n + 1) - DV;
    return t;
}
