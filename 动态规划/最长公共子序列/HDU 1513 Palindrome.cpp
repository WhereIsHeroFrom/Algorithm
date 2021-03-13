#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef char ValueType;
const int maxn = 5010;
int f[2][maxn];

int getLCSLength(int hsize, ValueType *h, int vsize, ValueType *v) {
    memset(f, 0, sizeof(f));
    int cur = 1, last = 0;
    for (int i = 1; i <= vsize; ++i) {
        for (int j = 1; j <= hsize; ++j) {
            if (v[i] == h[j]) {
                f[cur][j] = f[last][j - 1] + 1;
            }
            else {
                f[cur][j] = max(f[last][j], f[cur][j - 1]);
            }
        }
        swap(last, cur);
    }
    return f[last][hsize];
}

char s[2][maxn];
char t[1010];

int main() {
    int len[2];
    while (scanf("%d", &len[0]) != EOF) {
        len[1] = len[0];
        scanf("%s", &s[0][1]);

        for (int i = 1; i <= len[0]; ++i) {
            s[1][i] = s[0][len[0] + 1 - i];
        }
        printf("%d\n", len[0] - getLCSLength(len[0], s[0], len[1], s[1]));

    }
    return 0;
}
