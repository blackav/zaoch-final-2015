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
char s[20];
void check(char c) {  
  printf("%c\n", c);  
  fflush(stdout);
  gets(s);
  if (s[0] != 'N') {
    exit(0);
  }
}
void go(int len) {
  for (int i = 0; i < len; i++) {
    check('U');
    for (int j = 0; j < len * len; j++) {
      check('R');
    }
  }
  for (int i = 0; i < len * len; i++) {
    check('U');
    for (int j = 0; j < len; j++) {
      check('R');
    }
  }  
}
int main(){
  for (int i = 1;; i++) {
    go(i);
  }
  return 0;
}
