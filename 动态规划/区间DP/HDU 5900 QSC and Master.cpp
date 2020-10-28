#include <iostream>
#include <cstring>

using namespace std;

#define LL __int64
#define MAXN 310

int n;
int key[MAXN], val[MAXN];
bool fit[MAXN][MAXN];
bool canearse[MAXN][MAXN];
LL dp[MAXN][MAXN];
LL sum[MAXN][MAXN];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	int t;
	int i, j, k;

	scanf("%d", &t);

	while (t--) {
		memset(dp, 0, sizeof(dp));
		memset(canearse, 0, sizeof(canearse));
		memset(fit, 0, sizeof(fit));
		memset(sum, 0, sizeof(sum));

		scanf("%d", &n);

		for (i = 1; i <= n; ++i) {
			scanf("%d", &key[i]);
		}
		for (i = 1; i <= n; ++i) {
			scanf("%d", &val[i]);
		}

		for (i = 1; i <= n; ++i) {
			fit[i][i] = 0;
			sum[i][i] = val[i];
			for (j = i + 1; j <= n; ++j) {
				fit[i][j] = gcd(key[i], key[j]) > 1;
				sum[i][j] = sum[i][j - 1] + val[j];
			}
		}

		// Ã¶¾Ù³¤¶È
		for (i = 2; i <= n; i += 2) {
			for (int l = 1; l <= n; ++l) {
				int r = l + i - 1;
				if (fit[l][r]) {
					if (l + 1 == r) {
						canearse[l][r] = true;
					}
					else
						canearse[l][r] = canearse[l][r] || canearse[l + 1][r - 1];
				}

				for (k = l + 1; k + 1 < r; k += 2) {
					canearse[l][r] = canearse[l][r] || (canearse[l][k] && canearse[k + 1][r]);
					if (canearse[l][r]) break;
				}
			}
		}


		if (canearse[1][n]) {
			dp[1][n] = sum[1][n];
		}
		else {
			for (i = 1; i <= n; ++i) {
				for (int l = 1; l <= n; ++l) {
					int r = l + i - 1;
					if (canearse[l][r]) {
						dp[l][r] = sum[l][r];
					}
					else {
						for (k = l; k < r; ++k) {
							LL val = dp[l][k] + dp[k + 1][r];
							if (val > dp[l][r]) dp[l][r] = val;
							if (dp[l][r] == sum[l][r]) break;
						}
					}
				}
			}
		}

		printf("%I64d\n", dp[1][n]);
	}

	return 0;
}
/*
10
5
2 4 6 8 10
1 2 3 4 5

5
2 4 6 8 10
5 4 3 2 1

6
2 6 3 6 5 10
11 1 9 1 1 1

9
2 4 8 3 6 9 12 4 4
8 1 9 9 9 8 10 1 1111

10
9 7 2 3 4 4 3 2 7 2
1 1 1 1 1 1 1 1 1 1

9
5 5 2 3 3 2 6 6 5
0 1 1 1 1 1 1 1 1

8
7 3 3 5 2 2 5 7
1 1 1 1 1 1 1 1
*/
