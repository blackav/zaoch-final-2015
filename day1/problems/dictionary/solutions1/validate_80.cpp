#include <cstdio>
#include <cassert>
#include <cstring>

const int MAX_L = 5000;
const int MAX_N = 10000;
int l, n;
char s[MAX_N + 1];

int main() {
    scanf("%d%s", &l, s);
    assert(1 <= l && l <= MAX_L);
    n = strlen(s);
    assert(n >= 1 && n <= MAX_N);
    printf("2\na\nb\n");
    return 0;
}
