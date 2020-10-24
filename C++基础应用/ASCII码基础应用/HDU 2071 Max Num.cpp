// HDU 2071
// STL sort µÄÓ¦ÓÃ

#include <iostream>
#include <algorithm>
using namespace std;

double a[1000];

int main() {
	int t, i;
	int n;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%lf", &a[i]);
		}
		sort(a, a + n);
		printf("%.2lf\n", a[n - 1]);
	}
	return 0;
}
