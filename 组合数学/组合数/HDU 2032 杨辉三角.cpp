// HDU 2032
// 组合数学：杨辉三角，组合数
// c[i][j] = c[i - 1][j - 1] + c[i - 1][j];

#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64
#define MAXN 50

LL c[MAXN][MAXN];

int main() {
	int i, j;
	c[0][0] = 1;
	for (i = 1; i < MAXN; ++i) {
		for (j = 0; j <= i; ++j) {
			if (j == 0) {
				c[i][j] = 1;
			}
			else {
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			}
		}
	}
	int n;
	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; ++i) {
			for (j = 0; j <= i; ++j) {
				if (j) printf(" ");
				printf("%I64d", c[i][j]);
			}
			puts("");
		}
		puts("");
	}
	return 0;
}