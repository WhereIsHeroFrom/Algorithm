// HDU 2078
// 简单动态规划
// 所有课按照难度递减排序；
// dp[i][j] 代表 总共学习 j 门课，并且学习第 i 门课的最高效率值
// dp[i][j] = min{ dp[k][j-1] + (val[i] - val[k])^2 | 0 <= k < i} 
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 41

int val[MAXN];
int dp[MAXN][MAXN];
int n, m;

int sqr(int x) {
	return x * x;
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {

	int t;
	int i, j, k;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		val[0] = 100;
		for (i = 1; i <= n; ++i) {
			scanf("%d", &val[i]);
		}
		sort(val + 1, val + n + 1, cmp);
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 0;

		int ans = 0;

		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= m; ++j) {
				for (k = 0; k < i; ++k) {
					if (dp[k][j - 1] == -1) continue;
					int v = dp[k][j - 1] + sqr(val[i] - val[k]);
					if (dp[i][j] == -1 || v > dp[i][j]) {
						dp[i][j] = v;
						if (dp[i][j] > ans) ans = dp[i][j];
					}
				}
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}