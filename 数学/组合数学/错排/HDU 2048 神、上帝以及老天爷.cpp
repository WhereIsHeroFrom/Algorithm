// HDU 2048
// 简单动态规划、递推
// 组合数学：错排公式
// D[i] = (n-1)(D[i-1] + D[i-2]);

#include <iostream>
using namespace std;

__int64 D[100];
int n;

__int64 N(int v) {
	if (v == 0) return 1;
	return v * N(v - 1);
}

int main() {
	int i, j;
	D[0] = 1;
	D[1] = 0;
	for (i = 2; i < 100; ++i) {
		D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
		//printf("%d %I64d\n", i, D[i]);
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		double v = D[n] * 100.0 / N(n);
		printf("%.2lf%%\n", v);
	}
	return 0;
}