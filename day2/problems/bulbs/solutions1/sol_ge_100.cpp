#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);
const int size = 200 * 1000 + 100;

int n, k;
long long c, d;
int a[size], b[size];

long long ans = 0;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    scanf("%d%d%lld%lld", &n, &k, &c, &d);
    for (int i = 0; i < n; i++) {
    	scanf("%d%d", &a[i], &b[i]);
    	ans += (b[i] - a[i]) * 1ll * d;
    }

    vector <int> difs;
    for (int i = 0; i < n - 1; i++)
    	difs.pb(a[i + 1] - b[i]);
    sort(difs.begin(), difs.end());

   	long long md = max(0, ((n + k - 1) / k - 1)) * 1ll * c;
   	long long cur = 0ll;
   	for (int i = 0; i < n - 1; i++) {
   		cur += difs[i] * 1ll * d;
   		md = min(md, cur + max(0, ((n - 1 - i + k - 1) / k - 1)) * 1ll * c);	
   	}

   	cout << ans + md << endl;

    return 0;
}
