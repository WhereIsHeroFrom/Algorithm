// HDU 2021
// 多重背包的应用 
#include <iostream>
#include <cstring>
using namespace std;

#define MAXM 7
#define MAXN 10000
int v[MAXM] = { -1, 1, 2, 5, 10, 50, 100 };
int dp[MAXN][MAXM];

int main() {
	int n, i, j, k;
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (i = 0; i < MAXN; ++i) {
		for (j = 1; j < MAXM; ++j) {
			for (k = 0;; ++k) {
				int pre = i - k*v[j];
				if (pre < 0) break;
				//printf("%d %d %d\n", i, j, k);

				if (dp[pre][j - 1] == -1) continue;

				if (dp[i][j] == -1 || dp[pre][j - 1] + k < dp[i][j]){
					dp[i][j] = dp[pre][j - 1] + k;
				}
			}
		}
	}
	//printf("%d\n", dp[0][1]);


	while (scanf("%d", &n) != EOF && n) {
		int ans = 0;
		while (n--) {
			int m;
			scanf("%d", &m);
			ans += dp[m][MAXM - 1];
		}
		printf("%d\n", ans);
	}
	return 0;
}