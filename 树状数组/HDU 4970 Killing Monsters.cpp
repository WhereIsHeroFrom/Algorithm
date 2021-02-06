/*
    题意：一个塔防游戏，有 n(n <= 100000) 个位置, M (1 <= M <= 100000) 个塔，每个塔的攻击范围是 [Li, Ri]
    攻击力为 Di，现在给出 K 个怪，每个怪有 Hi 点血，问从 Xi 的 位置 走到 n, 有多少只怪可以活下来。

    题解：树状数组 + 离线算法
    1）首先对于所有的塔作：成段更新，单点求和。
        成段更新：add(Li, Di), add(Ri+1, -Di);
        单点求和：S[i] = sum(i);
    2）对所有的怪物，进行逆序排序，然后从 n开始累加 S[i]，和记为 T[i]，枚举怪物，当怪物的位置为 X[j] == i 的时候，判断
    H[j] > T[i] 则为存活，计数器 + 1；  
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
    while (x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

ll A[MAXV];
ll B[2][MAXV];
int n;

struct Monster {
    ll H;
    int x;
    void read() {
        scanf("%lld %d", &H, &x);
    }

    bool operator < (const Monster& m) {
        return x > m.x;
    }

}M[MAXV];

int main() {
    int i, j;
    int m, k;
    while (scanf("%d", &n) != EOF && n) {
        clear();
        scanf("%d", &m);
        while (m--) {
            int L, R, D;
            scanf("%d %d %d", &L, &R, &D);
            add(L, n, D);
            add(R + 1, n, -D);
        }
        scanf("%d", &k);
        for (i = 0; i < k; ++i) {
            M[i].read();
        }
        sort(M, M + k);

        ll s = 0;
        j = 0;
        int cnt = 0;
        for (i = n; i >= 1; --i) {
            s += sum(i);
            while(j < k && M[j].x == i) {
                if (M[j].H > s) {
                    ++cnt;
                }
                ++j;
            }
        }
        printf("%d\n", cnt);

    }
    return 0;
}