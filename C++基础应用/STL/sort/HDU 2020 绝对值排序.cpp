// HDU 2020
// STL sort 排序接口重载小于号的简单应用
#include <iostream>
#include <algorithm>
using namespace std;

struct Val {
	int v;
	int absv;
	bool operator < (const Val& other) {
		return absv > other.absv;
	}
}a[10000];

int main() {
	int n, i;
	while (scanf("%d", &n) != EOF && n) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i].v);
			a[i].absv = a[i].v < 0 ? -a[i].v : a[i].v;
		}
		sort(a, a + n);
		for (i = 0; i < n; ++i) {
			if (i) printf(" ");
			printf("%d", a[i].v);
		}
		puts("");

	}
	return 0;
}