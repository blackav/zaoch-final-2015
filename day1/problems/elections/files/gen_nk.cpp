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

int main(int argc, char ** argv) {
  registerGen(argc, argv, 1);
  
  if (argc != 3) {
    cerr << "Usage: n, k" << endl;    
    return 1;
  }

  ll MX = atoll(argv[1]);
  int K = atoi(argv[2]);

  cout << MX << " " << K << endl;
  
  return 0;
}
