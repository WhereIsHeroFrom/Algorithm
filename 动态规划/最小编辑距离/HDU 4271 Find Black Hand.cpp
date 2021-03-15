#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

typedef char ValueType;
const int maxn = 100150;
int f[maxn][12];
#define I 1
#define D 1
#define R 1

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int minEditCost(int ssize, ValueType *src, int tsize, ValueType *tar) {
    // f[i][j] 表示 src[1...i] 经过一些操作，将它的后缀 变成 tar[1...j] 的最小操作数
    f[0][0] = 0;

    // 原本是空串，却要和长度为 j 的匹配上，只能不断插入字符
    // 不断插入字符
    for (int j = 1; j <= tsize; ++j) {
        f[0][j] = f[0][j - 1] + I;
    }
    //printf("%s %s\n", src+1, tar+1);
    int ans = 1000000;
    for (int i = 1; i <= ssize; ++i) {
        f[i][0] = 0;
        for (int j = 1; j <= tsize; ++j) {
            int r = (src[i] == tar[j]) ? 0 : R;
            f[i][j] = min3(
                f[i - 1][j] + D,
                f[i][j - 1] + I,
                f[i - 1][j - 1] + r
                );
            if (j == tsize)
                ans = min(ans, f[i][j]);
            //printf("%d ", f[i][j]);
        }
        // puts("");
    }
    return ans;
}

ValueType A[maxn], B[20];
char ansB[20];

int main() {
    int Alen, Blen;
    int lim, n;
    while (scanf("%s", A + 1) != EOF) {
        int len = strlen(A + 1);
        scanf("%d", &n);
        int ans = 100000000;

        while (n--) {
            scanf("%s", B + 1);
            int lenB = strlen(B + 1);
            int curMin = 100000000;

            if (len < lenB) {
                // 暴力
                for (int i = 1; i <= len; ++i) {
                    A[len + i] = A[i];
                }
                for (int i = 0; i < len; ++i) {
                    int minv = minEditCost(len, A + i, lenB, B);
                    curMin = min(curMin, minv);
                }

            }
            else {
                // 接到环尾部
                for (int j = 1; j <= lenB; ++j) {
                    A[len + j] = A[j];
                }
                A[len + lenB + 1] = '\0';
                curMin = minEditCost(len + lenB, A, lenB, B);
            }

            if (curMin < ans) {
                ans = curMin;
                strcpy(ansB, B + 1);
            }
            else if (curMin == ans) {
                if (strcmp(ansB, B + 1) > 0) {
                    strcpy(ansB, B + 1);
                }
            }

        }
        printf("%s %d\n", ansB, ans);
    }
    return 0;
}

/*

*/