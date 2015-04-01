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
ll prev_prime(ll n) {
  while (n >= 2) {
    if (is_prime(n)) {
      return n;
    }
    n--;
  }
  assert(false);
}
int main(int argc, char ** argv) {
  registerGen(argc, argv, 1);
  
  if (argc != 4) {
    cerr << "Usage: n, k, is_equal" << endl;    
    return 1;
  }

  ll MX = atoll(argv[1]);
  int K = atoi(argv[2]);  
  int is_equal = atoi(argv[3]);  

  ll sq = (ll)pow((ld)MX, (ld)1. / K);

  if (is_equal) {
    ll pp = prev_prime(sq);
    ll n = 1;
    for (int i = 0; i < K; i++) {
      n *= pp;
    }
    cout << n << " " << K << endl;
  } else {
    ll pp = sq + 1;
    ll n = 1;
    for (int i = 0; i < K; i++) {
      pp = prev_prime(pp - 1);    
      n *= pp;
    }
    cout << n << " " << K << endl;
  }
  
  return 0;
}
