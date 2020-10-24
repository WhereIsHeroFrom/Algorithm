// HDU 2019
// STL sort 排序接口的简单应用
#include <iostream>
#include <algorithm>
using namespace std;

int a[10000];
int n, m;

int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		a[n++] = m;
		sort(a, a + n);
		for (i = 0; i < n; ++i) {
			if (i) printf(" ");
			printf("%d", a[i]);
		}
		puts("");

	}
	return 0;
}