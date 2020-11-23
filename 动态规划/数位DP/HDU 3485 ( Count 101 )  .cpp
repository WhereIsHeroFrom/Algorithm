#include <iostream>

using namespace std;

#define MAXN 100010
#define MOD 9997

int ans[MAXN];
int dp[MAXN][4];

int main() {
	int i, j;
	ans[0] = 1;
	ans[1] = 2;
	ans[2] = 4;
	ans[3] = 7;
	dp[3][0] = 2, dp[3][1] = 2, dp[3][2] = 2, dp[3][3] = 1;
	for (i = 4; i < MAXN; ++i) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];     // (后缀以"10"和"00"结尾的串加入一个字符"0"变成后缀为"00"结尾的)
		dp[i][1] = dp[i - 1][2] + dp[i - 1][3];     // (后缀以"11"和"001"结尾的串加入一个字符"0"变成后缀为"10"结尾的)
		dp[i][2] = dp[i - 1][2] + dp[i - 1][3];     // (后缀以"11"和"001"结尾的串加入一个字符"1"变成后缀为"11"结尾的)
		dp[i][3] = dp[i - 1][0];                  // (后缀以"00"结尾的串加入一个字符"1"变成后缀为"001"结尾的)
		for (j = 0; j < 4; ++j) {
			dp[i][j] %= MOD;
			ans[i] += dp[i][j];
			ans[i] %= MOD;
		}
	}
	int n;
	while (scanf("%d", &n) != EOF && n >= 0) {
		printf("%d\n", ans[n]);
	}
	return 0;
}