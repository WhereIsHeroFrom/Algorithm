/*
	树状数组 模板

	lowbit
	add
	sum

	Author: WhereIsHeroFrom
	Update Time: 2021-02-03
	Algorithm Complexity: O(log(n))
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll int
#define MAXN 11

ll c[MAXN][MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int idx, int x, int maxn, ll v) {
    while (x <= maxn) {
        c[idx][x] += v;
        x += lowbit(x);
    }
}

ll sum(int idx, int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[idx][x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

int n, m;

struct Query {
    int type;  // 0: S  1: Q
    int L, R;
    char D, P;
    int ans;
}Q[MAXV];

int a[MAXV], v[MAXV];

void addx(int P, int idx, int x, int addval) {
    for (int D = 1; D <= 10; ++D) {
        if (x == 0){
            if (P == 0) {
                add(D, idx, n, addval);
            }
            continue;

        }
        if (x % 10 == P) {
            add(D, idx, n, addval);
        }
        x /= 10;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        for (int i = 0; i < m; ++i) {
            char cmd[10];
            scanf("%s", cmd);
            if (cmd[0] == 'S') {
                Q[i].type = 0;
                scanf("%d %d", &Q[i].L, &Q[i].R);
            }
            else {
                Q[i].type = 1;
                scanf("%d %d %d %d", &Q[i].L, &Q[i].R, &Q[i].D, &Q[i].P);
            }
        }
        for (int P = 0; P <= 9; ++P) {
            clear();
            for (int i = 1; i <= n; ++i) {
                addx(P, i, a[i], 1);
                v[i] = a[i];
            }

            for (int i = 0; i < m; ++i) {
                if (Q[i].type == 0) {
                    addx(P, Q[i].L, v[ Q[i].L ], -1);
                    addx(P, Q[i].L, Q[i].R, 1);
                    v[Q[i].L] = Q[i].R;
                }
                else {
                    if (Q[i].P == P) {
                        Q[i].ans = sum(Q[i].D, Q[i].R) - sum(Q[i].D, Q[i].L - 1);
                    }
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            if (Q[i].type == 1) printf("%d\n", Q[i].ans);
        }
    }

    return 0;
}