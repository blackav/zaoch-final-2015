#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = (int) 2e5 + 10;
char s[N];
int z_a[N], z_b[N], used[N], it, l, n;
bool bad[N];

void calc_z(char * s, int * z) {
	z[0] = 0;
	for (int i = 1, l = 0, r = 0; s[i]; ++i) {
		z[i] = min(z[i - l], max(0, r - i + 1));
		while (s[z[i]] == s[i + z[i]])
			z[i]++, l = i, r = i + z[i] - 1;
	}
}

void print(char *s, int len) {
	for (int i = 0; i < len; ++i)
		printf("%c", s[i]);
	printf("\n");
}

int main() {
	scanf("%d%s", &l, s);
	n = strlen(s);
	calc_z(s, z_a);
	z_a[0] = l;
	for (int len_a = 1; len_a <= l; ++len_a) {
		if (bad[len_a]) continue;
		int start = len_a;
		while (z_a[start] >= len_a)
			start += len_a, bad[start] = true;
		if (start == n) {
			printf("1\n");
			print(s, len_a);
			return 0;
		}
	}
	for (int len_a = 1; len_a <= l; ++len_a) {
		if (bad[len_a]) continue;
		int start = len_a;
		while (z_a[start] >= len_a)
			start += len_a;
		calc_z(s + start, z_b + start);
		z_b[start] = l, ++it;
		for (int len_b = 1; len_b <= l; ++len_b) {
			int pos = start + len_b;
			while (used[pos] != it) {
				used[pos] = it;
				if (z_a[pos] >= len_a)
					pos += len_a;
				else if (z_b[pos] >= len_b)
					pos += len_b;
				else
					break;
			}
			if (pos == n) {
				printf("2\n");
				print(s, len_a);
				print(s + start, len_b);
				return 0;
			}
		}
	}
	printf("3\na\nb\nc\n");
	return 0;
}
