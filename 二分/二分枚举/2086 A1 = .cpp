// HDU 2087
// 二分
// A[i] = (A[i-1] + A[i+1])/2 - C[i]

// A[N+1] = 2 * (A[N] + C[N]) - A[N-1]; 
// ...
// A[4]   = 2 * (A[3] + C[3]) - A[2];
// A[3]   = 2 * (A[2] + C[2]) - A[1];
// A[2]   = 2 * (A[1] + C[1]) - A[0];
// 可见 A[N+1] 是相对于 A[1] 单调递增的，直接二分答案即可

#include <iostream>

using namespace std;

#define eps 1e-5
double A[10000], C[10000];
double AN_1;

int main() {
	int n, i;
	while (scanf("%d", &n) != EOF) {
		scanf("%lf %lf", &A[0], &AN_1);
		for (i = 1; i <= n; ++i) {
			scanf("%lf", &C[i]);
		}
		double l = -10000000000.0, r = 10000000000.0;
		while (r - l > eps) {
			double mid = (l + r) / 2;
			A[1] = mid;
			for (i = 2; i <= n + 1; ++i) {
				A[i] = 2 * (A[i - 1] + C[i - 1]) - A[i - 2];
			}

			if (A[n + 1] > AN_1) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		printf("%.2lf\n", l);
	}

	return 0;
}