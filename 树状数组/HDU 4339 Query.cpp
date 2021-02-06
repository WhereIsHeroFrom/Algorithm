/*
    题意：给定两个字符串 s1[0..l1], s2[0..l2]，两种操作：
    1）1 a i c 将第a个字符串的第i个字符设置为c；
    2）2 i 输出最大的 j 满足所有的 k (i<=k and k<i+j) s1[k] == s2[k]

    题解：二分答案 + 树状数组（单点更新，成段求和）
    首先，两个字符串相同的位为1，不同的位为0，插入到树状数组中；
    对于修改操作，0 变 1 或者 1 变 0 的情况，需要修改树状数组；
    对于查询操作，二分答案，然后在树状数组求和找到最大的连续 11111 的串；
*/

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 1000100
#define ll int

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    while (x <= maxn) {
        c[x] += v;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

char s[2][MAXV];
int l[2];
int maxLen;

int Max(int a, int b) {
    return a > b ? a : b;
}

int query(int idx) {

    int l = idx, r = maxLen;
    int sumpre = sum(idx - 1);
    int ans = idx - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;

        if (sum(mid) - sumpre == mid - idx + 1) {
            l = mid + 1;
            ans = mid;
        }
        else {
            r = mid - 1;
        }
    }

    return ans - idx + 1;
}

int main() {
    int t, i, Q, cas = 0;
    scanf("%d", &t);

    while (t--) {
        memset(s, '\0', sizeof(s));
        maxLen = 0;
        for (i = 0; i < 2; ++i) {
            scanf("%s", &s[i][1]);
            l[i] = strlen(&s[i][1]);
            maxLen = Max(l[i], maxLen);
        }
        clear();
        for (i = 1; i <= maxLen; ++i) {
            if (s[0][i] == s[1][i]) {
                add(i, maxLen, 1);
            }
        }

        scanf("%d", &Q);
        printf("Case %d:\n", ++cas);
        while (Q--) {
            int tp;
            int a, i;
            char cstr[10];

            scanf("%d", &tp);
            if (tp == 1) {
                scanf("%d %d %s", &a, &i, cstr);
                ++i;

                int prev = (s[0][i] == s[1][i]);
                s[a - 1][i] = cstr[0];
                int now = (s[0][i] == s[1][i]);
                if (prev == 1 && now == 0) {
                    add(i, maxLen, -1);
                }
                else if (prev == 0 && now == 1) {
                    add(i, maxLen, 1);
                }
            }
            else {
                scanf("%d", &i);
                ++i;
                printf("%d\n", query(i));
            }
        }
    }
    return 0;
}

/*
100

a
bb
1000
2 1
1 1 1 b
2 1

*/