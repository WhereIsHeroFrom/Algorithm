// HDU 2082
// 简单动态规划
// dp[i][j] 选择前面i个单词，组成价值为j的方案数
// dp[i][j] = sum{ dp[i - 1][j - k*i] | 0<=k<=cnt[i] }

#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64

int cnt[30];
LL dp[30][51];

int main() {
	int t, i, j, k;
	scanf("%d", &t);

	while (t--) {
		for (i = 1; i <= 26; ++i) {
			scanf("%d", &cnt[i]);
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (i = 1; i <= 26; ++i) {
			for (j = 0; j <= 50; ++j) {
				for (k = 0; k <= cnt[i]; ++k) {
					if (j - k*i < 0) break;
					dp[i][j] += dp[i - 1][j - k*i];
				}
			}
		}

		LL sum = 0;
		for (i = 1; i <= 50; ++i) {
			sum += dp[26][i];
		}
		printf("%I64d\n", sum);
	}

	return 0;
}