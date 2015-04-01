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
void upd(int l, int r) {
  int cnt = 0;
  if (a[l] - a[r] - 1 <= ans) return;
  for (int i = l + 1; i < r; i++) {
    C++;
    if (C % 1000 == 0) {
      if (clock() * 1. / CLOCKS_PER_SEC > 1.9) {
        cout << ansl << " " << ansr << endl;        
        exit(0);
      }
    }
    if (cnt + r - i <= ans) return;
    if (a[l] > a[i] && a[i] > a[r]) cnt++;
  }
  if (cnt > ans) {
    ans = cnt;
    ansl = l + 1;
    ansr = r + 1;
  }
}
int myrand(int n) {
  return ((rand() << 15) + rand()) % n;
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
  vector<int> l2 = l;
  #ifdef _WIN32
  random_shuffle(all(l2), myrand);
  #else
  random_shuffle(all(l2));
  #endif
  for (int i = 0; i < sz(l2); i++) {
    int p = lower_bound(all(r), l2[i] + 1) - r.begin();
    for (int j = p; j < sz(r) && a[l2[i]] > a[r[j]]; j++) {
      upd(l2[i], r[j]);
    }
  }
  cout << ansl << " " << ansr << endl;
  return 0;
}
