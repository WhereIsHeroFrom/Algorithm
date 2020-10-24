// HDU 2016
// 枚举最值，数值交换
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[200];

int main() {
	int i;
	int mIdx;
	while (scanf("%d", &n) != EOF && n) {
		mIdx = -1;
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			if (mIdx == -1 || a[i] < a[mIdx]) {
				mIdx = i;
			}
		}
		int tmp = a[0];
		a[0] = a[mIdx];
		a[mIdx] = tmp;
		for (i = 0; i < n; ++i) {
			if (i) {
				printf(" ");
			}
			printf("%d", a[i]);
		}
		puts("");
	}
	return 0;
}