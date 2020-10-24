// HDU 2014
// STL sort ”¶”√
#include <iostream>
#include <algorithm>
using namespace std;

int n;
double a[100];

int main() {
	int i;
	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; ++i) {
			scanf("%lf", &a[i]);
		}
		sort(a, a + n);
		double s = 0;
		for (i = 1; i < n - 1; ++i) {
			s += a[i];
		}
		s /= (n - 2);
		printf("%.2lf\n", s);
	}
	return 0;
}