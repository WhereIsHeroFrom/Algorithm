// HDU 2044
// 简单递推
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
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &a, &b);
		printf("%I64d\n", v[b - a]);
	}

	return 0;
}