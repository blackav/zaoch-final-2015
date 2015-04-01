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
#define problem_name "dictionary"
const int maxn = 100100;
int L, n;
char s[maxn];
int p[maxn];
vector<string> ans;
void calc_1() {
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && s[k] != s[i]) {
      k = p[k - 1];
    }
    if (s[k] == s[i]) {
      k++;
    }
    p[i] = k;
  }
  int d = n - p[n - 1];
  if (n % d != 0) {
    d = n;
  }
  if (n % d == 0 && d <= L && sz(ans) > 1) {
    ans.clear();
    string ss;
    for (int i = 0; i < d; i++) {
      ss += s[i];
    }
    ans.pb(ss);
  }
}
int main(){
  #ifdef home
  assert(freopen(problem_name".out","wt",stdout));
  assert(freopen(problem_name".in","rt",stdin));
  #endif
  scanf("%d", &L);
  scanf("%s", s);
  n = strlen(s);
  vector<bool> was(3);
  for (int i = 0; i < n; i++) {
    was[s[i] - 'a'] = true;
  }  
  for (int i = 0; i < 3; i++) if (was[i]) {
    string ss;
    ss += ('a' + i);
    ans.pb(ss);
  }
  calc_1();
  printf("%d\n", sz(ans));
  for (int i = 0; i < sz(ans); i++) {
    printf("%s\n", ans[i].c_str());
  }
  return 0;
}
