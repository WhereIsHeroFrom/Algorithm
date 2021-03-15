#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

typedef char ValueType;
const int maxn = 1010;
int f[maxn][2];
#define I 1
#define D 1
#define R 1

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int minEditCost(int ssize, ValueType *src, int tsize, ValueType *tar, int lim) {
    // f[i][j] 表示 src[1...i] 变成 tar[1...j] 后缀的最小操作数
    f[0][0] = 0;
    // 源串 到 空串的代价
    for (int i = 1; i <= ssize; ++i) {
        f[i][0] = f[i - 1][0] + D;
    }

    int cur = 1, last = 0;
    int pre = min(lim, ssize);
    int ans = 10000000;

    for (int j = 1; j <= tsize; ++j) {
        f[0][cur] = 0;

        for (int i = 1; i <= pre + 1; ++i) {
            int rcost = (src[i] == tar[j]) ? 0 : R;       // 替换的消耗

            f[i][cur] = min(
                f[i - 1][cur] + D,         // 源少1个，为了对齐目标，源需要删除1个字符
                f[i - 1][last] + rcost     // 源和目标 都 替换 最后一个字符
                );

            if (i != pre + 1) {
                f[i][cur] = min(
                    f[i][cur], f[i][last] + I            // 目标少1个，为了对齐目标，源需要插入1个字符
                    );
            }
            if (i == ssize) {
                ans = min(ans, f[i][cur]);
            }
            //printf("%d ", f[i][cur]);
        }
        //puts("");
        ++pre;
        while (pre >= ssize || f[pre][cur] > lim) {
            --pre;
        }
        swap(cur, last);
    }
    return ans != 10000000 ? ans : -1;
}

ValueType A[1000010], B[maxn];

int main() {
    int Alen, Blen;
    int lim;
    while (scanf("%s", A + 1) != EOF) {
        scanf("%s %d", B + 1, &lim);
        Alen = strlen(A + 1);
        Blen = strlen(B + 1);

        int dist = minEditCost(Blen, B, Alen, A, lim);
        printf("%d\n", dist);
    }
    return 0;
}

/*
AGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCAAGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCAAGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCA AGGCTGGCGCTAGGGAAAGAGCGCTA
10

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB
2

AGCCTTGCGA GCTAG
3

*/