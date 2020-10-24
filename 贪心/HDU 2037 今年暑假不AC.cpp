// HDU 2037
// 贪心
// STL sort 小于函数重载的应用
// 1. 按照结尾时间排序，如果结尾时间相同，开始时间晚的排前面（耗时短）；
// 2. 贪心枚举，不重叠则取出来并且标记结束时间；

#include <iostream>
#include <algorithm>
using namespace std;

struct Intval {
	int l, r;
	void Scanf() {
		scanf("%d %d", &l, &r);
	}

	bool operator < (const Intval& other) const {
		if (r == other.r) {
			return l < other.l;
		}
		return r < other.r;
	}
}I[1000];

int main() {
	int n, i;
	while (scanf("%d", &n) != EOF && n) {
		for (i = 0; i < n; ++i) {
			I[i].Scanf();
		}
		sort(I, I + n);
		int end = -1, c = 0;
		for (i = 0; i < n; ++i) {
			if (I[i].l >= end) {
				++c;
				end = I[i].r;
			}
		}
		printf("%d\n", c);
	}
	return 0;
}