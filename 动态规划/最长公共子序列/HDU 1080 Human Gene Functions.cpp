#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef char ValueType;
const int maxn = 2010;
const int SPACE = 4;
int f[2][maxn];

int matrix[5][5] = {
    { 5, -1, -2, -1, -3 },
    { -1, 5, -3, -2, -4 },
    { -2, -3, 5, -2, -2 },
    { -1, -2, -2, 5, -1 },
    { -3, -4, -2, -1, -100000000 },
};



int getLCS(int hsize, ValueType *h, int vsize, ValueType *v) {
    memset(f, 0, sizeof(f));
    int cur = 1, last = 0;
    f[last][0] = 0;
    for (int i = 1; i <= hsize; ++i) {
        f[last][i] = f[last][i - 1] + matrix[h[i]][SPACE];
    }

    for (int i = 1; i <= vsize; ++i) {
        int vc = v[i];
        f[cur][0] = f[last][0] + matrix[vc][SPACE];
        for (int j = 1; j <= hsize; ++j) {
            int hc = h[j];
            f[cur][j] = max(f[last][j] + matrix[vc][SPACE], f[cur][j - 1] + matrix[hc][SPACE]);
            if (vc == hc) {
                f[cur][j] = max(f[cur][j], f[last][j - 1] + matrix[vc][vc]);
            }
            else {
                f[cur][j] = max(f[cur][j], f[last][j - 1] + matrix[vc][hc]);
            }
            //printf("%d ", f[cur][j]);
        }
        swap(last, cur);
        //puts("");
    }
    return f[last][hsize];
}

char s[2][maxn];

#define maxn 2001
struct Test {
    int g[maxn];
};
int code[256];

int main() {

    code['A'] = 0;
    code['C'] = 1;
    code['G'] = 2;
    code['T'] = 3;
    code[' '] = 4;

    int len[2];
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %s %d %s", &len[0], &s[0][1], &len[1], &s[1][1]);
        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= len[i]; ++j) {
                s[i][j] = code[s[i][j]];
            }
        }
        printf("%d\n", getLCS(len[0], s[0], len[1], s[1]));

    }
    return 0;
}
