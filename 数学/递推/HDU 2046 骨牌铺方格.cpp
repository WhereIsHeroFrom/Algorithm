// HDU 2046
// 简单动态规划、递推
// 斐波那契数列

#include <iostream>
using namespace std;

__int64 v[100];


int main() {
	int t, i;
	int a, b;
	v[0] = 1;
	v[1] = 1;
	for (i = 2; i < 100; ++i) {
		v[i] = v[i - 1] + v[i - 2];
	}
	while (scanf("%d", &a) != EOF) {
		printf("%I64d\n", v[a]);
	}

	return 0;
}