// HDU 2011
// ∆Ê≈º–‘
#include <iostream>
using namespace std;

int n, m;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		double s = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			if (i & 1) {
				s += 1.0 / i;
			}
			else {
				s -= 1.0 / i;
			}
		}
		printf("%.2lf\n", s);
	}
	return 0;
}