#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <climits>
#include <cstring>
#include <complex>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <ctime>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pi;
typedef vector<int> vi;


#define all(c) (c).begin(),(c).end()
#define sz(c) (int)(c).size()

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define x first
#define y second
#define y1 y1_gdssdfjsdgf
#define y0 y0_fsdjfsdogfs
#define ws ws_fdfsdfsdgfs
#define image(a) {sort(all(a)),a.resize(unique(all(a))-a.begin());}
#define eprintf(...) {fprintf(stderr,__VA_ARGS__),fflush(stderr);}

#define forn(i,n) for( int i = 0 ; i < (n) ; i++ )
#define forit(it,c) for( __typeof((c).begin()) it = (c).begin() ; it != (c).end() ; it++ )
#define problem_name "permutation"
int n;
vector<int> a;
int ans = -1;
int ansl = -1;
int ansr = -1;
int C = 0;

int main(){
  #ifdef home
  assert(freopen(problem_name".out","wt",stdout));
  assert(freopen(problem_name".in","rt",stdin));
  #endif
  scanf("%d", &n);
  a.resize(n);
  vector<int> pref(n), suff(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }
  for (int i = 0; i < n - 1; i++) if (a[i] > a[i + 1]) {
    ans = 0;
    ansl = i + 1;
    ansr = i + 2;
  }
  vector<int> l, r;
  for (int i = 0; i < n; i++) {
    pref[i] = max(i == 0 ? 0 : pref[i - 1], a[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    suff[i] = min(i == n - 1 ? n : suff[i + 1], a[i]);
  }
  for (int i = 0; i < n; i++) {
    if (a[i] == pref[i]) {
      l.pb(i);
    }
    if (a[i] == suff[i]) {
      r.pb(i);
    }
  }
  vector<vector<pair<int, int> > > sans(sz(l));
  for (int i = 0; i < n; i++) {
    if (a[i] == pref[i] || a[i] == suff[i]) {
      continue;
    }
    int r1 = lower_bound(all(r), i) - r.begin();
    int r2 = r1;
    while (r2 < sz(r) && a[r[r2]] < a[i]) {
      r2++;
    }
    r2--;
    if (r1 > r2) continue;
    int l2 = lower_bound(all(l), i) - l.begin() - 1;
    int l1 = l2;
    while (l1 >= 0 && a[l[l1]] > a[i]) {
      l1--;
    }
    l1++;
    if (l1 > l2) continue;
    for (int li = l1; li <= l2; li++) {
      sans[li].pb(mp(r1, 1));
      sans[li].pb(mp(r2 + 1, -1));
    }
  }
  for (int i = 0; i < sz(l); i++) {
    if (sz(sans[i]) / 2 <= ans) continue;
    sort(all(sans[i]));
    int cc = 0;
    for (int j = 0; j < sz(sans[i]); j++) {      
      cc += sans[i][j].y;
      if (cc > ans) {
        ans = cc;
        ansl = l[i] + 1;
        ansr = r[sans[i][j].x] + 1;
      }
    }
  }  
  cout << ansl << " " << ansr << endl;
  return 0;
}
