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
const int maxn = 50000;
vector<int> g[maxn];
ll dp[2][maxn];
ll one[maxn];
ll xx[maxn];
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
vector<pair<ll, int> > f;
void reserve(int stp1, int rs, ll x, int i) {
  if (i == sz(f)) {
    g[stp1].reserve((rs + 1) / 2); 
    xx[stp1] = x;
    dp[0][stp1] = one[stp1] = (x + 1) / 2;
    return;
  }
  int S = f[i].y;  
  stp1 *= (S + 1);  
  for (int v1 = 0; v1 <= S; v1++, x *= f[i].x) {    
    reserve(stp1 + v1, rs * (v1 + 1), x, i + 1);
  }
}
void construct_edges(int stp1, int stp2, int i) {
  if (i == sz(f)) {
    if (xx[stp1] <= xx[stp2 - stp1]) {
      g[stp2].pb(stp1);
    }
    return;
  }
  int S = f[i].y;
  stp1 *= (S + 1);
  stp2 *= (S + 1);  
  for (int v1 = 0; v1 <= S; v1++) {
    for (int v2 = v1; v2 <= S; v2++) {
      construct_edges(stp1 + v1, stp2 + v2, i + 1);
    }
  }
}

const ll MAX_N = ll(1e13);
const int MAX_K = 10;

int main() {        
  #ifdef home
  freopen(TASK".in", "r", stdin);
  freopen(TASK".out", "w", stdout);
  #endif
  ll n;
  int k;
  cin >> n >> k;
  assert(1 <= n && n <= MAX_N);
  assert(1 <= k && k <= MAX_K);
  ll inf = n + 1;
  f = factorize(n);    
  reserve(0, 1, 1, 0);
  construct_edges(0, 0, 0);
  int v1 = 0;
  for (int i = 0; i < sz(f); i++) {
    v1 = v1 * (f[i].y + 1) + f[i].y;
  }
  int cur = 0;
  int lg = 0;
  while ((1 << lg) <= k) {
    lg++;
  }
  lg--;
  assert((k >> lg) & 1);
  for (int i = lg - 1; i >= 0; i--) {
    {
      int ncur = cur ^ 1;
      ll* dp1 = dp[cur];
      ll* dp2 = dp[ncur];
      ll val;    
      for (int j = 0; j <= v1; j++) {
        dp2[j] = inf;
        for (int it = 0; it < sz(g[j]); it++) {
          if (dp2[j] > (val = dp1[g[j][it]] * dp1[j - g[j][it]])) {
            dp2[j] = val;
          }
        }
      }
      cur = ncur;
    }
    if ((k >> i) & 1) {
      int ncur = cur ^ 1;
      ll* dp1 = dp[cur];
      ll* dp2 = dp[ncur];
      ll val;    
      for (int j = 0; j <= v1; j++) {
        dp2[j] = inf;
        for (int it = 0; it < sz(g[j]); it++) {
          if (dp2[j] > (val = one[g[j][it]] * dp1[j - g[j][it]])) {
            dp2[j] = val;
          }          
        }
      }
      cur = ncur;
    }
  }
  cout << dp[cur][v1] << endl;
//  cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
  return 0; 
}
