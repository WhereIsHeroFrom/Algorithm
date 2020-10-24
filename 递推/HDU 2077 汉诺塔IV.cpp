// HDU 2077
// 简单递推
// f[i] 表示从左边移动到右边，得到递推： f[i] = 3 * f[i - 1] + 2;
// g[i] 表示从左边移动到中间，得到递推： g[i] = f[i - 1] + 1 + g[i - 1];

// 方案数 = 2*(g[n-1]+1)
#include <iostream>

using namespace std;

#define LL __int64

LL f[100], g[100];

LL Min(LL a, LL b) {
	return a < b ? a : b;
}

int main() {
	int t, i;
	int n;
	f[1] = 2;
	g[1] = 1;
	for (i = 2; i < 100; ++i) {
		f[i] = 3 * f[i - 1] + 2;
		g[i] = f[i - 1] + 1 + g[i - 1];
	}

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		printf("%I64d\n", 2 + 2 * g[n - 1]);
	}
	return 0;
}