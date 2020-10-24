// HDU 2070
// 简单递推：斐波那契数列

#include <iostream>
using namespace std;

#define LL __int64
#define MAXN 101

LL f[MAXN];

int main() {
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i < MAXN; ++i) {
		f[i] = f[i - 1] + f[i - 2];
	}
	int n;
	while (scanf("%d", &n) != EOF && n >= 0) {
		printf("%I64d\n", f[n]);
	}

	return 0;
}