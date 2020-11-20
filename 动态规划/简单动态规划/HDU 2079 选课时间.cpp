// HDU 2079
// 多重背包问题

// dp[i][j] 表示 前 i 种物品组合出 j 分的方案数
// dp[i][j] = sum { dp[i - 1][j - score[i] * l] | 0<=l<=cnt[i] }

#include <iostream>
#include <cstring>
#include <algorithm>

#define LL __int64

int n, k;
LL dp[10][41];
int score[10], cnt[10];

int main() {
	int t;
	int i, j, l;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &k);

		for (i = 1; i <= k; i++) {
			int a, b;
			scanf("%d %d", &score[i], &cnt[i]);
		}

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (i = 1; i <= k; ++i) {
			for (j = 0; j <= n; j++) {
				for (l = 0; l <= cnt[i]; ++l) {
					if (j - score[i] * l < 0) {
						continue;
					}
					dp[i][j] += dp[i - 1][j - score[i] * l];
				}
			}
		}

		printf("%I64d\n", dp[k][n]);
	}

	return 0;
}