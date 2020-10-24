
// HDU 2088
// Ì°ÐÄ
// STL sort

#include <iostream>
#include <algorithm>
using namespace std;

int a[100];
int t = 0;

int main() {
	int i, j;
	int n;
	while (scanf("%d", &n) != EOF && n) {
		if (t++) puts("");
		int s = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			s += a[i];
		}
		s /= n;
		sort(a, a + n);
		int c = 0;
		for (i = 0; i < n; ++i) {
			if (a[i] < s) {
				int need = s - a[i];
				a[i] = s;
				for (j = n - 1; j > i; --j) {
					if (a[j] == s) {
						continue;
					}
					if (a[j] <= s) break;
					if (a[j] - s >= need) {
						c += need;
						a[j] -= need;
						break;
					}
					else {
						c += a[j] - s;
						need -= a[j] - s;
						a[j] = s;
					}
				}
			}
		}
		printf("%d\n", c);
	}
	return 0;
}