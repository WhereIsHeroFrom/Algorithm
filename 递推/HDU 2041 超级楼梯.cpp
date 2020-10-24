// HDU 2041
// 数学递推：斐波那契数列
#include <iostream>
using namespace std;
#define LL __int64

LL X[100];
int n;

int main() {
	int i;
	X[1] = 1;
	X[2] = 1;
	for (i = 3; i < 50; ++i) {
		X[i] = X[i - 1] + X[i - 2];
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%I64d\n", X[n]);
	}
	return 0;
}