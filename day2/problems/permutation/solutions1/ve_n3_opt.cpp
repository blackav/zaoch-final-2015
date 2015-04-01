#include <cstdio>
#include <numeric>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define y0 y3487465
#define y1 y8687969
#define fill(x,y) memset(x,y,sizeof(x))
#define prev PREV
                         
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef double D;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

template<class T> T abs(T x) { re x > 0 ? x : -x; }

int n;
int m;

int x[1000000];

int main () {
	scanf ("%d", &n);
	for (int i = 0; i < n; i++) scanf ("%d", &x[i]);
	int ans = 0, ai = -2, aj = -2;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			if (x[i] < x[j]) continue;
			if (2 * (j - i) - 1 <= ans || 2 * (x[i] - x[j]) - 1 <= ans) continue;
			int cur = 1;
			for (int k = i + 1; k < j; k++)
				cur += 2 * int (x[i] > x[k] && x[k] > x[j]);
			if (cur > ans) {
				ans = cur;
				ai = i;
				aj = j;
			}
		}
	printf ("%d %d\n", ai + 1, aj + 1);
	return 0;
}