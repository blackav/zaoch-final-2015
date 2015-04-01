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
void go(ll n, int k, ll cur) {
  if (k == 1) {
    cur = cur * (n + 1) / 2;
    if (cur < ans) {
      ans = cur;
    }
    return;
  }
  for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
    go(n / i, k - 1, cur * (i + 1) / 2);
    if (i * i != n) {
      go(i, k - 1, cur * (n / i + 1) / 2);
    }
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
