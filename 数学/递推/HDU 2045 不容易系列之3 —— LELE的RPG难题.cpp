// HDU 2045
// 简单动态规划、递推
// dp[i][j][k] 表示 第1个格子为 颜色j，第i个格子为 颜色k 的方案数
// 最后统计 sum{ dp[n][a][b], a != b }

#include <iostream>
using namespace std;

__int64 dp[100][4][4];

int main() {
	dp[1][0][0] = dp[1][1][1] = dp[1][2][2] = 1;

	int i, j, k, l;
	for (i = 2; i < 100; ++i) {
		for (j = 0; j < 3; ++j) {
			for (k = 0; k < 3; ++k) {
				dp[i][j][k] = 0;
				for (l = 0; l < 3; ++l) {
					if (k != l) dp[i][j][k] += dp[i - 1][j][l];
				}
			}
		}
	}
	int n;

	while (scanf("%d", &n) != EOF) {
		if (n == 1) {
			printf("3\n");
			continue;
		}
		__int64 ans = 0;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; ++j) {
				if (i != j) ans += dp[n][i][j];
			}
		}
		printf("%I64d\n", ans);
	}


	return 0;
}