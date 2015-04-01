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
const int MAXSH = (1 << 21) + 10;
pair<int, int> rm[MAXSH];
int d[MAXSH];
void init(int v, int l, int r) {
  rm[v] = mp(0, l);
  d[v] = 0;
  if (l == r) {
    return;
  }
  int m = (l + r) / 2;
  init(v * 2, l, m);
  init(v * 2 + 1, m + 1, r);
}
void push(int v) {
  if (d[v] != 0) {
    rm[v].x += d[v];
    if (v * 2 + 1 < MAXSH) {
      d[v * 2] += d[v];
      d[v * 2 + 1] += d[v];
    }
    d[v] = 0;
  }
}
void add(int v, int l, int r, int l1, int r1, int val) {
  assert(l <= l1 && l1 <= r1 && r1 <= r);
  push(v);
  if (l == l1 && r == r1) {
    d[v] += val;
    push(v);
    return;    
  }
  int m = (l + r) / 2;
  if (l1 <= m) {
    add(v * 2, l, m, l1, min(r1, m), val);
  } else {
    push(v * 2);
  }
  if (r1 > m) {
    add(v * 2 + 1, m + 1, r, max(l1, m + 1), r1, val);
  } else {
    push(v * 2 + 1);
  }
  rm[v] = max(rm[v * 2], rm[v * 2 + 1]);
}
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
  if (ans == -1) {
    cout << ansl << " " << ansr << endl;    
    return 0;
  }
  vector<int> l, r, lv, rv;
  for (int i = 0; i < n; i++) {
    pref[i] = max(i == 0 ? 0 : pref[i - 1], a[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    suff[i] = min(i == n - 1 ? n : suff[i + 1], a[i]);
  }
  for (int i = 0; i < n; i++) {
    if (a[i] == pref[i]) {
      l.pb(i);
      lv.pb(a[i]);
    }
    if (a[i] == suff[i]) {
      r.pb(i);
      rv.pb(a[i]);
    }
  }
  vector<vector<pair<int, int> > > st(sz(l)), en(sz(l));
  for (int i = 0; i < n; i++) {
    if (a[i] == pref[i] || a[i] == suff[i]) {
      continue;
    }
    int r1 = lower_bound(all(r), i) - r.begin();
    int r2 = lower_bound(all(rv), a[i]) - rv.begin() - 1;
    if (r1 > r2) continue;
    int l1 = lower_bound(all(lv), a[i]) - lv.begin();
    int l2 = lower_bound(all(l), i) - l.begin() - 1;
    if (l1 > l2) continue;
    st[l1].pb(mp(r1, r2));
    en[l2].pb(mp(r1, r2));
  }
  int ko = 0;
  init(1, 0, sz(r) - 1);
  for (int i = 0; i < sz(l); i++) {
    for (int j = 0; j < sz(st[i]); j++) {
      ko++;
      add(1, 0, sz(r) - 1, st[i][j].x, st[i][j].y, 1);
    }    
    if (rm[1].x > ans) {
      ans = rm[1].x;
      ansl = l[i] + 1;
      ansr = r[rm[1].y] + 1;
    }
    for (int j = 0; j < sz(en[i]); j++) {      
      ko--;
      add(1, 0, sz(r) - 1, en[i][j].x, en[i][j].y, -1);
    }
  }  
  cout << ansl << " " << ansr << endl;
  return 0;
}
