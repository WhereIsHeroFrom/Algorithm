// HDU 2052
// 标准输入输出

#include <iostream>
using namespace std;

int main() {
	int n, m;
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF) {
		printf("+");
		for (i = 0; i < n; ++i) printf("-");
		printf("+\n");

		for (i = 0; i < m; ++i) {
			printf("|");
			for (j = 0; j < n; ++j) printf(" ");
			printf("|\n");
		}

		printf("+");
		for (i = 0; i < n; ++i) printf("-");
		printf("+\n");
		puts("");
	}

	return 0;
}