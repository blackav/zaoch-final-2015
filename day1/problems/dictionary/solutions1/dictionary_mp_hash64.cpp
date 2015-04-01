#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int64 long long
const int N = (int) 1e5 + 10;
const int P = 17239;
char s[N];
int used[N], l, n;
int64 h[N], ppow[N];
bool bad[N];

void print(char *s, int len) {
        for (int i = 0; i < len; ++i)
                printf("%c", s[i]);
        printf("\n");
}

int main() {
        scanf("%d%s", &l, s);
        n = strlen(s);
        h[0] = 0, ppow[0] = 1;
        for (int i = 0; i < n; ++i) {
                h[i + 1] = h[i] * P + s[i];
                ppow[i + 1] = ppow[i] * P;
        }
        for (int len_a = 1; len_a <= l; ++len_a) {
                if (bad[len_a]) continue;
                int start = len_a;
                int64 ha = h[len_a];
                while (h[start + len_a] - h[start] * ppow[len_a] == ha)
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
                int64 ha = h[len_a];
                while (h[start + len_a] - h[start] * ppow[len_a] == ha)
                        start += len_a;
                for (int len_b = 1; len_b <= l; ++len_b) {
                        int pos = start + len_b;
                        int64 hb = h[start + len_b] - h[start] * ppow[len_b];
                        while (used[pos] != len_a) {
                                used[pos] = len_a;
                                if ((pos + len_a <= n) && (h[pos + len_a] - h[pos] * ppow[len_a] == ha)) {
                                        pos += len_a;
                                        continue;
                                }
                                if ((pos + len_b <= n) && (h[pos + len_b] - h[pos] * ppow[len_b] == hb)) {
                                        pos += len_b;
                                        continue;
                                }
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
