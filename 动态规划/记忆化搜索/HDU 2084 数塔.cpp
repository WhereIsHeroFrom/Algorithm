// HDU 2084
// 简易动态规划，记忆化搜索

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXN 120

int n;
int a[MAXN][MAXN];
int dp[MAXN][MAXN];

int dfs(int x, int y) {
	if (x == 0) {
		return a[0][0];
	}
	if (dp[x][y] != -1) {
		return dp[x][y];
	}
	int Max = INT_MIN;
	if (x > y) {
		dp[x - 1][y] = dfs(x - 1, y);
		if (dp[x - 1][y] > Max) Max = dp[x - 1][y];
	}

	if (y > 0) {
		dp[x - 1][y - 1] = dfs(x - 1, y - 1);
		if (dp[x - 1][y - 1] > Max) Max = dp[x - 1][y - 1];
	}

	return dp[x][y] = (Max + a[x][y]);
}

int main() {
	int t;
	int i, j;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			for (j = 0; j <= i; ++j) {
				scanf("%d", &a[i][j]);
			}
		}
		memset(dp, -1, sizeof(dp));
		int Max = INT_MIN;
		for (i = 0; i < n; ++i) {
			dp[n - 1][i] = dfs(n - 1, i);
			if (dp[n - 1][i] > Max) Max = dp[n - 1][i];
		}
		printf("%d\n", Max);
	}

	return 0;
}