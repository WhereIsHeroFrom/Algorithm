#include <iostream>

using namespace std;

#define MAXN 210

int n, L;
int dp[MAXN][MAXN][MAXN];
int a[MAXN];

int color[MAXN], num[MAXN];
int cal[1000];

int sqr(int x) {
	if (cal[x] == -1) {
		cal[x] = x * x;
	}
	return cal[x];
}

int dfs(int l, int r, int k) {
	if (l > r) {
		return 0;
	}

	if (dp[l][r][k] != -1) {
		return dp[l][r][k];
	}

	int iMax = dfs(l, r - 1, 0) + sqr(num[r] + k);

	for (int i = l; i < r; ++i) {

		if (color[i] == color[r]) {
			int val = dfs(l, i, num[r] + k) + dfs(i + 1, r - 1, 0);
			if (val > iMax) {
				iMax = val;
			}
		}
	}

	return dp[l][r][k] = iMax;
}

int main() {
	int t;
	int i;
	int cas = 0;
	memset(cal, -1, sizeof(cal));

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		L = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			if (i == 0 || a[i] != a[i - 1]) {
				color[++L] = a[i];
				num[L] = 1;
			}
			else {
				++num[L];
			}
		}

		memset(dp, -1, sizeof(dp));

		dp[1][L][0] = dfs(1, L, 0);
		printf("Case %d: %d\n", ++cas, dp[1][L][0]);
	}

	return 0;
}