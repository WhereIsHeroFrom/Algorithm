// HDU 2069
// ¶àÖØ±³°ü

#include <iostream>

using namespace std;

#define MAXN 255
#define MAXM 110
#define MAXC 6
#define LL __int64

int Coin[] = {
	0, 1, 5, 10, 25, 50
};

LL dp[MAXC][MAXN][MAXM];

int main() {
	int n;
	int i, j, k, l;
	dp[0][0][0] = 1;

	for (k = 1; k <= 5; ++k) {
		for (i = 0; i < MAXN; ++i) {
			for (j = 0; j < MAXM; ++j) {
				for (l = 0;; ++l) {
					if (i - l*Coin[k] < 0) break;
					if (j - l < 0) break;

					dp[k][i][j] += dp[k - 1][i - l*Coin[k]][j - l];

				}
			}
		}
	}

	while (scanf("%d", &n) != EOF) {
		LL ans = 0;
		if (n < 0) {
			ans = 0;
		}
		else if (n == 0) {
			ans = 1;
		}
		else {
			for (i = 0; i <= 100; ++i)
				ans += dp[5][n][i];
		}
		printf("%I64d\n", ans);
	}

	return 0;
}