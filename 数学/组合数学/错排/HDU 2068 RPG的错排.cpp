// HDU 2068
// 组合数学：错排公式
//           组合公式
// D[n] = (n-1) * (D[n-1] + D[n-2]);
// C[i][j] = C[i-1][j] + C[i-1][j-1];

#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 101

LL C[MAXN][MAXN];
LL D[MAXN];

int main() {
	C[0][0] = 1;
	D[0] = 1;
	D[1] = 0;
	int i, j;
	for (i = 1; i < MAXN; ++i) {
		for (j = 0; j < MAXN; ++j) {
			if (j == 0) {
				C[i][j] = 1;
			}
			else {
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			}
		}
	}

	for (i = 2; i < MAXN; ++i) {
		D[i] = (LL)(i - 1) * (D[i - 1] + D[i - 2]);
	}

	int n;
	while (scanf("%d", &n) != EOF && n) {
		LL ans = 0;
		for (i = (n + 1) / 2; i <= n; ++i) {
			ans += C[n][i] * D[n - i];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}