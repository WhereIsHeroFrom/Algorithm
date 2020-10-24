// HDU 2010
// 预处理初始化
#include <iostream>
using namespace std;

int n, m;
int all[1000];
int val[1000];

int main() {
	all[99] = 0;
	for (int i = 100; i <= 999; ++i) {
		int v0 = i / 100;
		int v1 = i / 10 % 10;
		int v2 = i % 10;
		val[i] = (i == v0*v0*v0 + v1*v1*v1 + v2*v2*v2) ? 1 : 0;
		all[i] = all[i - 1] + val[i];
	}

	while (scanf("%d %d", &n, &m) != EOF && n) {
		int v = all[m] - all[n - 1];
		if (!v) {
			printf("no\n");
		}
		else {
			int hasoutput = false;
			for (int i = n; i <= m; ++i) {
				if (val[i]) {
					if (hasoutput) {
						printf(" ");
					}
					printf("%d", i);
					hasoutput = true;
				}
			}
			puts("");
		}
	}
	return 0;
}