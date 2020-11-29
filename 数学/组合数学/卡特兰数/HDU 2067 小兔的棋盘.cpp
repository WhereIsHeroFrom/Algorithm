// HDU 2067
// 组合数学：卡特兰数
// 简单动态规划、递推

#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 110

LL f[MAXN][MAXN];

int main() {
	int i, j;
	int n;

	for (i = 0; i < MAXN; ++i) {
		for (j = 0; j < MAXN; j++) {
			if (i == 0 && j == 0) {
				f[i][j] = 1;
			}
			else if (i == 0) {
				f[i][j] = f[i][j - 1];
			}
			else if (j == 0) {
				f[i][j] = f[i - 1][j];
			}
			else {
				f[i][j] = f[i][j - 1];
				if (i != j) {
					f[i][j] += f[i - 1][j];
				}
			}
		}
	}

	int t = 0;
	while (scanf("%d", &n) != EOF && n >= 0) {
		printf("%d %d %I64d\n", ++t, n, f[n][n] * 2);
	}

	return 0;
}
