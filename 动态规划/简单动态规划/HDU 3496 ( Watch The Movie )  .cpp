#include <iostream>

using namespace std;

#define maxn 101
#define inf -1

int dp[maxn][maxn][1001];
int n, m, l;

struct point {
	int tim;
	int val;
}pt[maxn];

int Max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int t;
	int i, j, k;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &m, &l);
		for (i = 1; i <= n; i++) {
			scanf("%d %d", &pt[i].tim, &pt[i].val);
		}
		for (i = 0; i <= n; i++) {
			for (j = 0; j <= m; j++) {
				for (k = 0; k <= l; k++) {
					dp[i][j][k] = inf;
				}
			}
		}
		dp[0][0][0] = 0;

		for (i = 1; i <= n; i++) {
			for (j = 0; j <= m && j <= i; j++) {
				for (k = 0; k <= l; k++) {
					if (j && k >= pt[i].tim && dp[i - 1][j - 1][k - pt[i].tim] != -1)
						dp[i][j][k] = Max(dp[i][j][k], dp[i - 1][j - 1][k - pt[i].tim] + pt[i].val);

					if (i - 1 >= j)
						dp[i][j][k] = Max(dp[i][j][k], dp[i - 1][j][k]);
				}
			}
		}
		int MMax = 0;
		for (i = 0; i <= l; i++) {
			if (dp[n][m][i] > MMax)
				MMax = dp[n][m][i];
		}
		printf("%d\n", MMax);
	}
	return 0;
}