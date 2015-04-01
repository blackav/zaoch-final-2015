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
#define problem_name "bulbs"
int n, k, c, d, cur_seg, cur_len;
ll ans = (ll)8e18;
void upd() {
  ans = min(ans, (ll)c * ((cur_seg + k - 1) / k - 1) + (ll)d * cur_len);
}
int main(){
  #ifdef home
  assert(freopen(problem_name".out","wt",stdout));
  assert(freopen(problem_name".in","rt",stdin));
  #endif
  scanf("%d%d%d%d", &n, &k, &c, &d);
  vector<int> len;
  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &l[i], &r[i]);
    if (i > 0) {
      len.pb(l[i] - r[i - 1]);
    }
  }
  sort(all(len));
  cur_seg = 1;
  cur_len = r[n - 1] - l[0];
  upd();
  for (int i = sz(len) - 1; i >= 0; i--) {
    cur_seg++;
    cur_len -= len[i];
    upd();
  }
  cout << ans << endl;
  return 0;
}
