#include <cstdio>
#include <cstring>
const int N = (int) 2e5 + 1;
int l, n;
char s[N];

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
	for (int len_1 = 1; len_1 <= l; ++len_1) {
		int pos = 0;
		while (strncmp(s, s + pos, len_1) == 0) pos += len_1;
		for (int len_2 = 1; len_2 <= l; ++len_2) {
			int cur = pos + len_2;
			while (true)
				if (strncmp(s, s + cur, len_1) == 0)
					cur += len_1;
				else if (strncmp(s + pos, s + cur, len_2) == 0)
					cur += len_2;
				else
					break;
			if (cur == n) {
				printf("%d\n", 2);
				print(s, len_1);
				print(s + pos, len_2);
				return 0;
			}
		}
	}
	printf("3\na\nb\nc\n");
	return 0;
}
