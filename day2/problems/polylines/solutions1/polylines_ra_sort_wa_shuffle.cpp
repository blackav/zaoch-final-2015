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
#define problem_name "polylines"
int n;
vector<vector<pair<int, int> > > v;
bool cmp(int i, int j) {
  bool up = false;
  bool dw = false;
  int it1 = 0;
  int it2 = 0;
  while (it1 < sz(v[i]) && it2 < sz(v[j])) {    
    if (v[i][it1].x < v[j][it2].x) {
      int it3 = max(0, it2 - 1);
      ll val = (ll)(v[i][it1].x - v[j][it3].x) * (v[j][it3 + 1].y - v[j][it3].y) - (ll)(v[j][it3 + 1].x - v[j][it3].x) * (v[i][it1].y - v[j][it3].y);
      if (val > 0) {
        up = true;
      } else
      if (val < 0) {
        dw = true;
      }
      it1++;
    } else {
      int it3 = max(0, it1 - 1);
      ll val = (ll)(v[i][it3 + 1].x - v[i][it3].x) * (v[j][it2].y - v[i][it3].y) - (ll)(v[j][it2].x - v[i][it3].x) * (v[i][it3 + 1].y - v[i][it3].y);
      if (val > 0) {
        up = true;
      } else
      if (val < 0) {
        dw = true;
      }
      it2++;
    }
  }
  if (up && dw) {
    printf("No\n%d %d\n", i + 1, j + 1);
    exit(0);
  }
  if (up) {
    return true;
  }
  if (dw) {
    return false;
  }
  return i < j;
}
vector<int> g;
bool cmp2(int i, int j) {
  if (v[i][0].y != v[j][0].y) {
    return v[i][0].y < v[j][0].y;    
  }
  return g[i] < g[j];
}
int myrand(int n) {
  return ((rand() << 15) + rand()) % n;
}
int main(){
  #ifdef home
  assert(freopen(problem_name".out","wt",stdout));
  assert(freopen(problem_name".in","rt",stdin));
  #endif
  int A, B;
  scanf("%d %d", &A, &B);
  scanf("%d", &n);
  v.resize(n);
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    k++;
    for (int j = 0; j < k; j++) {
      int x, y;
      scanf("%d %d", &x, &y);
      v[i].pb(mp(x, y));
    }
  }
  vector<int> p(n);
  g.resize(n);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    g[i] = i;
  }
  while (clock() * 1. / CLOCKS_PER_SEC < 1.9) {
    #ifdef _WIN32
    random_shuffle(all(g), myrand);    
    #else
    random_shuffle(all(g));    
    #endif
    sort(all(p), cmp2);
    for (int i = 0; i + 1 < n; i++) {
      cmp(p[i], p[i + 1]);
    }
  }
  printf("Yes\n");
  return 0;
}
