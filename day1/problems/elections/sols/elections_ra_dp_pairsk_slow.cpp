#include <iostream>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
typedef long double ld;

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define next next_fdsgd
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()
#define TASK "elections"
const int maxn = 100000;
vector<pair<int, ll> > g[maxn];
ll dp[30][maxn];
vector<pair<ll, int> > factorize(ll n) {
  vector<pair<ll, int> > res;
  for (ll i = 2; i * i <= n; i++) {
    int cnt = 0;
    while (n % i == 0) {
      n /= i;
      cnt++;
    }
    if (cnt) {
      res.pb(mp(i, cnt));
    }
  }
  if (n > 1) {
    res.pb(mp(n, 1));
  }
  return res;
}
ll ans = (ll)9e18;
void construct_edges(vector<pair<ll, int> >& n, vector<int>& stp1, vector<int>& stp2, int i) {
  if (i == -1) {
    int h1 = 0;
    int h2 = 0;
    ll curv = 1;
    for (int j = 0; j < sz(n); j++) {
      h1 = h1 * (n[j].y + 1) + stp1[j];
      h2 = h2 * (n[j].y + 1) + stp2[j];
      ll ss = 1;
      for (int l = stp1[j]; l < stp2[j]; l++) {
        ss *= n[j].x;
      }
      curv = curv * ss;
    }
    g[h2].pb(mp(h1, (curv + 1) / 2));
    return;
  }
  for (int v1 = 0; v1 <= n[i].y; v1++) {
    for (int v2 = v1; v2 <= n[i].y; v2++) {
      stp1[i] = v1;
      stp2[i] = v2;
      construct_edges(n, stp1, stp2, i - 1);
    }
  }
}
bool is_prime(int x) {
  for (int i = 2; i * i <= x; i++) if (x % i == 0) {
    return false;
  }
  return true;
}
int main() {        
  #ifdef home
  freopen(TASK".in", "r", stdin);
  freopen(TASK".out", "w", stdout);
  #endif
  ll n;
  int k;
  cin >> n >> k;
  vector<pair<ll, int> > f = factorize(n);  
/*  auto f = factorize(1);
  int M = 20;
  int S = 2;
  double cc = 1;
  int K = 1;
  for (int i = 3; i <= M; i++) if (is_prime(i)) {
    cc *= pow(i, S);
    K *= (S + 1);
    f.pb(mp(i, S));
  }
  k = 5;
  cerr << cc << " " << K << endl;*/
  
  vector<int> stp1(sz(f));
  vector<int> stp2(sz(f));  
  construct_edges(f, stp1, stp2, sz(f) - 1);
  int v1 = 0;
  for (int i = 0; i < sz(f); i++) {
    v1 = v1 * (f[i].y + 1) + f[i].y;
  }
  dp[0][v1] = 1;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j <= v1; j++) if (dp[i][j]) {
      for (int it = 0; it < sz(g[j]); it++) {
        const pair<int, ll>& t = g[j][it];
        if (dp[i + 1][t.x] == 0 || dp[i + 1][t.x] > dp[i][j] * t.y) {
          dp[i + 1][t.x] = dp[i][j] * t.y;
        }
      }
    }
  }
  cout << dp[k][0] << endl;
  //cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
  return 0; 
}
