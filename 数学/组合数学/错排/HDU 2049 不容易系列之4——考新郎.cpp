// HDU 2049
// 简单动态规划、递推
// 组合数学：错排公式、组合公式
// D[i] = (n-1)(D[i-1] + D[i-2]);
// C[i][j] = C[i-1][j-1] + C[i-1][j];

#include <iostream>
using namespace std;

__int64 D[100], C[100][100];
int n, m;

int main() {
	int i, j;
	D[0] = 1;
	D[1] = 0;
	for (i = 2; i < 100; ++i) {
		D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
		//printf("%d %I64d\n", i, D[i]);
	}
	C[0][0] = 1;
	for (i = 1; i < 100; ++i) {
		for (j = 0; j < 100; ++j) {
			if (j == 0) C[i][j] = 1;
			else {
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
		}
	}


	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		__int64 v = C[n][m] * D[m];
		printf("%I64d\n", v);
	}
	return 0;
}