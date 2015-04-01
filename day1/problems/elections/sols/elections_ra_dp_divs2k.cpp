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

int main() {
  #ifdef home
  freopen(TASK".in", "r", stdin);
  freopen(TASK".out", "w", stdout);
  #endif
  ll n;
  int k;
  cin >> n >> k;
  ll inf = n + 1;
  vector<ll> divs;  
  for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
    divs.pb(i);
    divs.pb(n / i);    
  }  
  sort(all(divs));
  divs.resize(unique(all(divs)) - divs.begin());  
  vector<vector<ll> > dp(2, vector<ll>(sz(divs), inf));
  dp[0][0] = 1;
  int cur = 0;
  for (int it = 1; it <= k; it++) {
    int ncur = cur ^ 1;
    vector<ll>& dp1 = dp[ncur];
    vector<ll>& dp2 = dp[cur];
    for (int i = 0; i < sz(divs); i++) {
      dp1[i] = inf;
      for (int j = 0; j <= i; j++) if (divs[i] % divs[j] == 0 && dp2[j] != inf) {       
        dp1[i] = min(dp1[i], dp2[j] * ((divs[i] / divs[j]) + 1) / 2);
      }
    }
    cur = ncur;
  }
  cout << dp[cur][sz(divs) - 1] << endl;
  return 0; 
}
