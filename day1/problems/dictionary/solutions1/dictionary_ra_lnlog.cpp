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
const int maxn = 30100;
const int maxL = 15001;
int L, n;
char s[maxn];
int p[maxn];
int z1[maxn];
int z2[maxn];

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
inline bool good(int n, int a, int b) {
  return true;
}
void calc_z(int* z, char* s, int n) {
  z[0] = n;
  int maxl = 0;
  int maxr = 0;
  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - maxl], maxr - i));
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      z[i]++;
    }
    if (i + z[i] > maxr) {
      maxl = i;
      maxr = i + z[i];
    }
  }
}
int C = 0;
void calc_2() {
  if (sz(ans) <= 2) return;
  calc_z(z1, s, n);
  for (int l1 = 1; l1 <= L; l1++) {
    int pos = l1;
    while (pos + l1 <= n && z1[pos] >= l1) {
      pos += l1;
    }
    calc_z(z2, s + pos, n - pos);
    for (int l2 = 1; l2 <= min(L, n - pos); l2++) if (good(n - pos, l1, l2)) {
      int pos2 = pos + l2;
      while (pos2 < n) {
        C++;
        if (C == 1000) {
          if (clock() * 1./ CLOCKS_PER_SEC > 1.9) {
            return;
          }
          C = 0;
        }
        if (pos2 + l1 <= n && z1[pos2] >= l1) {
          pos2 += l1;
        } else 
        if (pos2 + l2 <= n && z2[pos2 - pos] >= l2) {
          pos2 += l2;
        } else {
          break;
        }
      }
      if (pos2 == n) {
        ans.clear();
        string ss;
        for (int i = 0; i < l1; i++) {
          ss += s[i];
        }
        ans.pb(ss);
        ss = "";
        for (int i = 0; i < l2; i++) {
          ss += s[pos + i];
        }
        ans.pb(ss);
        return;
      }
    }
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
  s[n] = '#';
  L = min(L, n);
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
  calc_2();
  printf("%d\n", sz(ans));
  for (int i = 0; i < sz(ans); i++) {
    printf("%s\n", ans[i].c_str());
  }
  return 0;
}
