/*
    题意：给定N(N <= 100000)个灯泡，0表示关，1表示开。现在有一种开关可以改变任意连续的K只灯泡的状态。
求最少需要多少个开关才能使所有的0变成1。
    题解：贪心 + 树状数组。
    从左往右按顺序找到状态为0的灯泡i应用一次开关，那么紧接着[i+1, i+K-1]个灯泡的状态都改变了。
由于K有可能很大，所以每次改变状态不遍历所有的灯泡，而是在i位置+1，i+K的位置-1。然后求位置i的灯泡状态
只要取前i个灯泡状态量的和即可。单点更新，成段求和，树状数组维护即可。

*/
#include <iostream>

using namespace std;

#define MAXN 100010
#define LL __int64

int n, k;
LL c[MAXN];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int v) {
    while(x <= n) {
        c[x] += v;
        x += lowbit(x);
    }
}

LL sum(int x) {
    LL s = 0;
    while(x) {
        s += c[x];
        x -= lowbit(x);
    }
    return s;
}

char str[MAXN];

int main() {
    int i;
    while(scanf("%d %d", &n, &k) != EOF) {
        if( !n && !k ) break;
        memset(c, 0, sizeof(c));
        scanf("%s", &str[1]);
        int ans = 0;
        for(i = 1; i <= n; ++i) {
            if( (sum(i) + (str[i]-'0')) & 1 ) {
                continue;
            }
            if(i + k > n+1 || k == 0) {
                ans = -1;
                break;
            }
            ++ans;
            add(i, 1);
            add(i+k, -1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
