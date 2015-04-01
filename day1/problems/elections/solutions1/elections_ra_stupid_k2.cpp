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
  if (k == 1) {
    cout << (n + 1) / 2 << endl;
    return 0;
  }
  int ans = n;
  assert(k == 2);
  for (int k1 = 1; k1 <= n; k1++) if (n % k1 == 0) {
    int k2 = n / k1;
    ans = min(ans, (k1 + 1) / 2 * (k2 + 1) / 2);
  }
  cout << ans << endl;
  return 0; 
}
