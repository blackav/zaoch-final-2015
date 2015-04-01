#include <cstdio>
#include <cstring>
const int N = (int) 2e5 + 1;
int l, n;
char s[N];
bool good[N];

void print(char *s, int len) {
	for (int i = 0; i < len; ++i)
		printf("%c", s[i]);
	printf("\n");
}

int main() {
	scanf("%d%s", &l, s), n = strlen(s);
	for (int len_1 = 1; len_1 <= l; ++len_1) {
		int pos = 0;
		while (strncmp(s, s + pos, len_1) == 0) pos += len_1;
		if (pos == n) {
			printf("%d\n", 1);
			print(s, len_1);
			return 0;
		}
	}
	for (int len_1 = 1; len_1 <= l; ++len_1)
		for (int start_2 = 1; start_2 < n; ++start_2)
			for (int len_2 = 1; (len_2 + start_2 <= n) && (len_2 <= l); ++len_2) {
				memset(good, 0, (n + 1) * sizeof(good[0]));
				good[0] = true;
				for (int i = 0; i < n; ++i)
					if (good[i]) {
						if (strncmp(s, s + i, len_1) == 0)
							good[i + len_1] = true;
						if (strncmp(s + start_2, s + i, len_2) == 0)
							good[i + len_2] = true;
					}
				if (good[n]) {
					printf("%d\n", 2);
					print(s, len_1);
					print(s + start_2, len_2);
					return 0;
				}
			}
	printf("3\na\nb\nc\n");
	return 0;
}
