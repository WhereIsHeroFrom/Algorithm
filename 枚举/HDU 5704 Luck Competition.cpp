#include <iostream>

using namespace std;

#define MAXN 100010

int n, a[MAXN];
int has[MAXN];

int main() {
	int t;
	int i, j;
	scanf("%d", &t);

	while (t--) {
		memset(has, 0, sizeof(has));
		scanf("%d", &n);
		int sum = 0;
		for (i = 0; i < n - 1; ++i) {
			scanf("%d", &a[i]);
			++has[a[i]];
			sum += a[i];
		}
		double maxPro = 0;
		int maxVal = -1;

		for (i = 100; i >= 0; --i) {
			double K = (sum + i)*1.0 / n;
			double M = K * 2 / 3;
			if (i > M) continue;
			bool flag = 0;
			for (j = i + 1; j <= M; ++j) {
				if (has[j]) {
					flag = 1;
					break;
				}
			}
			if (flag) continue;
			double p = 1.0 / (has[i] + 1);
			if (p > maxPro) {
				maxPro = p;
				maxVal = i;
			}
		}
		printf("%d %.2lf\n", maxVal, maxPro);
	}
	return 0;
}