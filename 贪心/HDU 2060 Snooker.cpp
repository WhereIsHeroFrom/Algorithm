// HDU 2060
// 贪心：读懂 斯诺克 规则
// 核心是：如果打了红球，再打彩球，彩球是可以被拿出来继续打的；

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n, a, b;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &a, &b);
		int v;
		if (n < 6) {
			v = (15 - n) * n / 2;
		}
		else {
			// 红球：n-6
			// 彩球：6个，分数 2/3/4/5/6/7
			v = 1 * (n - 6) + 7 * (n - 6) + 2 + 3 + 4 + 5 + 6 + 7;
		}
		if (v + a >= b) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}