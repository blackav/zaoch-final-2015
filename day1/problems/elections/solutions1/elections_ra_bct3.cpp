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

ll ans = (ll)9e18;
map<pair<ll, int>, ll> dp;
map<ll, vector<ll> > divs;
void go(ll n, int k, ll cur) {
  if (k == 1) {
    cur = cur * (n + 1) / 2;
    if (cur < ans) {
      ans = cur;
    }
    return;
  }
  map<pair<ll, int>, ll>::iterator it1 = dp.find(mp(n, k));
  if (it1 == dp.end()) {
    dp[mp(n, k)] = cur;
  } else
  if (it1->y < cur) {
    return;
  } else {
    it1->y = cur;
  }
  map<ll, vector<ll> >::iterator it = divs.find(n);
  if (it == divs.end()) {
    divs[n] = vector<ll>();
    it = divs.find(n);
    for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
      it->y.pb(i);
      if (i * i != n) {
        it->y.pb(n / i);
      }
    }  
  }
  for (int j = 0; j < sz(it->y); ++j) {
    go(n / it->y[j], k - 1, cur * (it->y[j] + 1) / 2);    
  }
}
int main() {
  #ifdef home
  freopen(TASK".in", "r", stdin);
  freopen(TASK".out", "w", stdout);
  #endif
  ll n;
  int k;
  cin >> n >> k;
  go(n, k, 1);
  cout << ans << endl;
//  cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
  return 0; 
}
