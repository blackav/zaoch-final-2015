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
#define problem_name "segments"

int ans;
vector<int> a;
void upd(int x, int d) {
  if (x < 0) return;
  if (a[x] != a[x + 1]) {
    ans += d;
  }
}
int main(){

  int n, q;
  scanf("%d", &n);
  a.resize(n + 1);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  a[n] = (int)1e9 + 1;
  ans = 0;
  for (int i = 0; i < n; i++) {
    upd(i, 1);
  }
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    x--;
    upd(x, -1);
    upd(x - 1, -1);
    a[x] = y;
    upd(x, 1);
    upd(x - 1, 1);
    printf("%d\n", ans);
  }
  return 0;
}
