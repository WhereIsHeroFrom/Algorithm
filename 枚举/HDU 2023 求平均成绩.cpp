// HDU 2023
// 浮点数判相等，不能用 == ，>=和<= 都是安全的， > 和 < 都不安全
// 枚举、除法
#include <iostream>
using namespace std;

int c[100][100];
double val[2][100];

int main() {
	int n, m;
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(val, 0, sizeof(val));

		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				scanf("%d", &c[i][j]);
			}
		}

		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				val[0][i] += c[i][j];
			}
			val[0][i] /= m;
		}
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				val[1][i] += c[j][i];
			}
			val[1][i] /= n;
		}
		int cnt = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if (!(c[i][j] >= val[1][j])) {
					break;
				}
			}
			if (j == m) cnt++;
		}

		for (i = 0; i < n; ++i) {
			if (i) printf(" ");
			printf("%.2lf", val[0][i]);
		}
		puts("");
		for (i = 0; i < m; ++i) {
			if (i) printf(" ");
			printf("%.2lf", val[1][i]);
		}
		puts("");
		printf("%d\n\n", cnt);
	}
	return 0;
}
