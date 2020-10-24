// HDU 2098
// 数论：素数筛选

#include <iostream>

using namespace std;

#define MAXN 1000000

bool f[MAXN];

int main() {
	int n;

	int i, j;
	f[1] = 1;
	for (i = 2; i < MAXN; ++i) {
		if (!f[i]) {
			for (j = i * i; j < MAXN && j >= 0; j += i) {
				f[j] = 1;
			}
		}
	}

	while (scanf("%d", &n) != EOF && n) {
		int c = 0;
		for (i = 1; i <= n / 2; ++i) {
			if (!f[i] && !f[n - i] && i != n - i) ++c;
		}
		printf("%d\n", c);
	}
	return 0;
}