#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100200;
const int MOD = 1000000;

int cnt[MAXN];
int val;
int dp[2][MAXN];
int v[MAXN];

int main() {
    int n;
    int i, j, k;
    int T, S, B;
    while (scanf("%d %d %d %d", &T, &n, &S, &B) != EOF) {
        for (i = 1; i <= T; ++i) {
            cnt[i] = 0;
        }
        for (i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            cnt[x] ++;
        }
        // 相同的数归为一组
        // dp[i][j] 前 i 组中选择 j 个数的方案数
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int sum = 0;
        int l, r;
        int last = 0, cur = 1;
        for (i = 1; i <= T; ++i) {
            memset(v, 0, sizeof(v));

            for (j = 0; j <= B; ++j) {
                if (dp[last][j]) {
                    l = j;
                    r = j + cnt[i];
                    v[l] = (v[l] + dp[last][j]) % MOD;
                    v[r + 1] = (v[r + 1] - dp[last][j] + MOD) % MOD;
                }
            }

            for (j = 0; j <= B; ++j) {
                if (j) {
                    v[j] += v[j - 1];
                    if (v[j] >= MOD) v[j] %= MOD;
                }
                dp[cur][j] = v[j];
            }

            last ^= 1;
            cur ^= 1;
        }
        int ans = 0;
        for (i = S; i <= B; ++i) {
            ans = (ans + dp[last][i]) % MOD;
        }
        printf("%d\n", ans);

    }
    return 0;
}

/*
15 160 1 128
1 1 1 1 2 2 2 2 2 3 3 3 4 4 5 5
1 1 1 1 2 2 2 2 2 3 3 3 4 4 5 5
1 1 1 1 2 2 2 2 2 3 3 3 4 4 5 5
1 1 1 1 2 2 2 2 2 3 3 3 4 4 5 5
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7
7 8 9 7 8 9 7 8 9 7 8 9 7 8 9 7

10 3 1 3
5
6
7
*/