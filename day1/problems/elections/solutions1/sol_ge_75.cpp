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

const int size = 20 * 1000;
const int ssize = 11;

long long ans[ssize][size];
long long n;
int k;

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n >> k;
    vector <long long> divs;
    for (int i = 1; i * 1ll * i <= n; i++) {
    	if (n % i == 0) {
    		divs.pb(i);
    		divs.pb(n / i);
    	}
    }

    sort(divs.begin(), divs.end());
    divs.resize(unique(divs.begin(), divs.end()) - divs.begin());

    int m = divs.size();

    for (int i = 0; i < m; i++)
    	ans[1][i] = (divs[i] + 1) / 2;
    for (int i = 2; i <= k; i++)
    	for (int j = 0; j < m; j++) {
    		ans[i][j] = ans[i - 1][j];
    		for (int k = 0; k <= j; k++)
    			if (divs[j] % divs[k] == 0) {
    				ans[i][j] = min(ans[i][j], ans[i - 1][k] * ((divs[j] / divs[k] + 1) / 2));
    			}
    	}

    cout << ans[k][m - 1] << endl;

    return 0;
}
