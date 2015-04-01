#include <cstdio>
#include <algorithm>
using namespace std;
#define int64 long long
const int N = (int) 2e5 + 10;
int n, k, c, d, len[N], a[N], b[N];
int64 sum, ans;

int main() {
	scanf("%d%d%d%d", &n, &k, &c, &d);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &a[i], &b[i]), sum += (b[i] - a[i]) * (int64) d;
	for (int i = 0; i + 1 < n; ++i)
		len[i] = a[i + 1] - b[i];
	sort(len, len + n - 1);
	int64 ans = sum + max(0, (n + k - 1) / k - 1) * (int64) c;
	for (int i = 1; i <= n - 1; ++i) {
		sum += len[i - 1] * (int64) d;
		ans = min(ans, sum + max(0, (n - i + k - 1) / k - 1) * (int64) c);
	}
	printf("%lld\n", ans);
	return 0;
}
