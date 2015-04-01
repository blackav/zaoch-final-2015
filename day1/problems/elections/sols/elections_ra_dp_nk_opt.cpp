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
  vector<vector<int> > dp(2, vector<int>(n + 1, n + 1));
  dp[0][1] = 1;
  int cur = 0;
  for (int it = 1; it <= k; it++) {
    int ncur = cur ^ 1;
    for (int i = 1; i <= n; i++) if (n % i == 0) {
      dp[ncur][i] = n + 1;
      for (int j = 1; j <= i; j++) if (i % j == 0 && dp[cur][j] <= n) {       
        dp[ncur][i] = min(dp[ncur][i], dp[cur][j] * ((i / j) + 1) / 2);
      }  
    }
    cur = ncur;
  }
  cout << dp[cur][n] << endl;
  return 0; 
}
