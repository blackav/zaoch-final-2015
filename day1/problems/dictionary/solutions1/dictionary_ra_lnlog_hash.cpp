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
const int maxn = 110000;
//const int maxL = 5001;
//int gcd[maxL][maxL];
int L, n;
char s[maxn];
int p[maxn];
int z1[maxn];
int z2[maxn];
int h[maxn];
ll stp[maxn];
const int md = (int)1e9 + 7;
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
  return true;//n % gcd[a][b] == 0;
}
int C = 0;
bool jump(int& x, const int len, const ll val) { 
  bool res = false;
  while ((h[x] - val - h[x + len] * stp[len]) % md == 0) {
    C++;
    if (C == 1000) {
      if (clock() * 1./ CLOCKS_PER_SEC > 1.9) {
        printf("%d\n", sz(ans));
        for (int i = 0; i < sz(ans); i++) {
          printf("%s\n", ans[i].c_str());
        }   
        exit(0);
      }
      C = 0;
    }
    x += len;
    res = true;
  }
  return res;
}
void calc_2() {
  if (sz(ans) <= 2) return;
/*  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= L; j++) {
      if (gcd[i][j] == 0) {
        for (int c = 1; max(i, j) * c <= L; c++) {
          gcd[i * c][j * c] = c;
        }
      }
    }
  }*/
  h[n] = 0;
  stp[0] = 1;
  for (int i = 1; i <= n; i++) {
    stp[i] = (stp[i - 1] * 239) % md;
  }
  for (int i = n - 1; i >= 0; i--) {
    h[i] = (h[i + 1] * stp[1] + s[i] - 'a' + 1) % md;
  }
  for (int l1 = 1; l1 <= L; l1++) {
    int pos = 0;
    ll val1 = h[0] - h[l1] * stp[l1];
    jump(pos, l1, val1);
    for (int l2 = 1; l2 <= min(L, n - pos); l2++) if (good(n - pos, l1, l2)) {
      ll val2 = h[pos] - h[pos + l2] * stp[l2];      
      int pos2 = pos;
      while (1) {
        if (!jump(pos2, l2, val2)) break;
        if (!jump(pos2, l1, val1)) break;
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
