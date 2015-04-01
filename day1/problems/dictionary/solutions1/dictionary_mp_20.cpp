#include <cstdio>
#include <cstring>

int l, n;
char s[111];

int main() {
	scanf("%d%s", &l, s), n = strlen(s);
	for (int i = 1; i <= l; ++i)
		if ((n % i == 0) && (strncmp(s, s + i, n - i) == 0)) {
			s[i] = 0;
			printf("1\n%s\n", s);
			return 0;
		}
	printf("2\na\nb\n");
	return 0;
}

