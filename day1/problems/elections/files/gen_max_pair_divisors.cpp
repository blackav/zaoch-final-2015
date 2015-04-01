#include <iostream>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <algorithm>
#include <cstring>
#include "testlib.h"

using namespace std;

typedef long long ll;
typedef long double ld;

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define next next_fdsgd
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

bool is_prime(int x) {
  for (int i = 2; i * i <= x; i++) if (x % i == 0) {
    return false;
  }
  return true;
}
vector<int> p;
ld my_pow(ld x, int s) {
  if (s == 0) return 1;
  ld res = my_pow(x, s / 2);
  res = res * res;
  if (s % 2 == 1) {
    res = res * x;
  }
  return res;
}
pair<ld, ld> Ans = mp(-1, -1);
void getMaxD(int i, int max_stp, ld curn, ld curd, ld MX) {
  if (i == sz(p)) {
    Ans = max(Ans, mp(curd, curn));
    return;
  }
  for (int j = max_stp; j >= 0; j--) {
    ld new_curn = curn * my_pow(p[i], j);
    if (new_curn > MX) continue;
    ld new_curd = curd * (j + 1) * (j + 2) / 2;    
    getMaxD(i + 1, j, new_curn, new_curd, MX);
  }
}
int main(int argc, char ** argv) {
  registerGen(argc, argv, 1);
  
  if (argc != 3) {
    cerr << "Usage: n, k" << endl;    
    return 1;
  }

  ll MX = atoll(argv[1]);
  int K = atoi(argv[2]);  

  for (int i = 2; i < 100; i++) {
    if (is_prime(i)) {
      p.pb(i);
    }
  }
  getMaxD(0, 30, 1, 1, MX);
  cout<<(ll)Ans.y<<" "<<K<<endl;
  return 0;
}
