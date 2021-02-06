/*
    题意：给定一个长度为 n(n <= 50000) 的数组 A，只由 b 和 w 组成，两种操作：
    1） 0 L R： 找出区间 [L, R] 中有多少个 wbw；
    2） 1 k ch：将第 k 个字符变成 ch；
    题解：树状数组 / 单点更新
    
    1）首先一遍预处理：
        n = len - 2
        如果连续3个字符是 bwb 则在对应的树状数组中插入1，否则就是 0
        012         ->  1
        123         ->  2
        234         ->  3
        k(k+1)(k+2) ->  k+1

    2）对于 0 操作，询问树状数组  SUM(L+1，R-1) 的和;
    3) 对于 1 操作，第 k 个字符能够影响的树状数组的位置为 
        (k-2)(k-1)k   ->  k-1
        (k-1)k(k+1)   ->  k
        k(k+1)(k+2)   ->  k+1

*/

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll long long

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
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

ll sum(int l, int r) {
    if (l > r) {
        return 0;
    }
    return sum(r) - sum(l - 1);
}

char str[MAXV];
int len;

int cnt(int a, int b, int c) {
    if (c >= len || a < 0) {
        return 0;
    }
    return (str[a] == 'w' && str[b] == 'b' && str[c] == 'w') ? 1 : 0;
}

int main() {
    int t, cas = 0;
    int n, m;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        scanf("%s", str);
        clear();
        len = n;
        for (int i = 0; i + 2 < n; ++i) {
            int v = cnt(i, i + 1, i + 2);
            add(i + 1, n - 2, v);
        }
        printf("Case %d:\n", ++cas);
        while (m--) {
            int tp;
            scanf("%d", &tp);
            if (tp == 0) {
                int L, R;
                scanf("%d %d", &L, &R);
                printf("%d\n", sum(L+1, R-1));
            }
            else {
                int k;
                char ch[10];
                scanf("%d %s", &k, ch);
                for (int i = 0; i < 3; ++i) {
                    char tmp = str[k];
                    int pre = cnt(k - i, k - i + 1, k - i + 2);
                    str[k] = ch[0];
                    int now = cnt(k - i, k - i + 1, k - i + 2);
                    str[k] = tmp;
                    if (pre == 1 && now == 0) {
                        add(k - i + 1, n - 2, -1);
                    }
                    else if(pre == 0 &&now == 1) {
                        add(k - i + 1, n - 2, 1);
                    }
                }
                str[k] = ch[0];
            }
        }

    }

    return 0;
}
