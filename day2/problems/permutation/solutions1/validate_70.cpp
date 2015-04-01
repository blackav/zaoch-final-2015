#include <cstdio>
#include <numeric>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <deque>
#include <cassert>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define y0 y3487465
#define y1 y8687969
#define fill(x,y) memset(x,y,sizeof(x))
#define prev PREV
                         
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef double D;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

template<class T> T abs(T x) { re x > 0 ? x : -x; }

const int N = 1 << 20;

int n;
int m;

int x[N];
ii tree[2 * N + 10];
int same[2 * N + 10];
vi p, q;
vii vp[N];
vii vn[N];
ii y[N];
ii z[N];

ii build (int x, int l, int r) {
    if (l == r) re tree[x] = mp (0, l);
    int s = (l + r) / 2;
    re tree[x] = max (build (x * 2 + 1, l, s), build (x * 2 + 2, s + 1, r));
}

void push (int x, int l, int r) {
    if (same[x] != 0) {
        if (l != r) {
            same[x * 2 + 1] += same[x];
            same[x * 2 + 2] += same[x];
        }
        tree[x].fi += same[x];
        same[x] = 0;
    }
}

ii add (int x, int l, int r, int lc, int rc, int y) {
    push (x, l, r);
    if (r < lc || l > rc) re tree[x];
    if (l >= lc && r <= rc) {
        same[x] += y;
        push (x, l, r);
        re tree[x];
    }
    int s = (l + r) / 2;
    tree[x] = max (add (x * 2 + 1, l, s, lc, rc, y), add (x * 2 + 2, s + 1, r, lc, rc, y));
    re tree[x];
}

const int MAX_N = 75 * 1000;
bool used[MAX_N + 10];

int main () {
    scanf ("%d", &n);
    assert(n >= 1 && n <= MAX_N);
    for (int i = 0; i < n; i++) {
        scanf ("%d", &x[i]);
        assert(x[i] >= 1 && x[i] <= n);
        assert(!used[x[i]]);
        used[x[i]] = true;
    }
    vi p, q;
    for (int i = 0; i < n; i++)
        if (p.empty () || x[i] > x[p.back ()]) {
            p.pb (i);
            y[i] = mp (-1, -1);
        } else {
            int l = -1, r = sz (p) - 1;
            while (r - l > 1) {
                int s = (l + r) / 2;
                if (x[p[s]] > x[i]) r = s; else l = s;
            }
            y[i] = mp (r, sz (p) - 1);
        }
    for (int i = n - 1; i >= 0; i--)
        if (q.empty () || x[i] < x[q.back ()]) {
            q.pb (i);
            z[i] = mp (-1, -1);
        } else {
            int l = -1, r = sz (q) - 1;
            while (r - l > 1) {
                int s = (l + r) / 2;
                if (x[q[s]] < x[i]) r = s; else l = s;
            }
            z[i] = mp (r, sz (q) - 1);
        }
    for (int i = 0; i < n; i++) {
        if (y[i].fi == -1 || z[i].fi == -1) continue;
        vp[y[i].fi].pb (mp (z[i].fi, z[i].se));
        vn[y[i].se].pb (mp (z[i].fi, z[i].se));
    }
    build (0, 0, sz (q) - 1);
    int ans = 0, ai = -2, aj = -2;
    for (int i = 0; i < sz (p); i++) {
        for (int j = 0; j < sz (vp[i]); j++)
            add (0, 0, sz (q) - 1, vp[i][j].fi, vp[i][j].se, 1);
        if (tree[0].fi > 0 && tree[0].fi + 1 > ans) {
            ans = tree[0].fi + 1;
            ai = p[i];
            aj = q[tree[0].se];
        }
        for (int j = 0; j < sz (vn[i]); j++)
            add (0, 0, sz (q) - 1, vn[i][j].fi, vn[i][j].se, -1);
    }
    if (ans == 0) {
        for (int i = 0; i + 1 < n; i++)
            if (x[i] > x[i + 1]) {
                ans = 1;
                ai = i;
                aj = i + 1;
            }
    }
    printf ("%d %d\n", ai + 1, aj + 1);
    return 0;
}
