// HDU 2035
// 数论：二分幂快速模

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL __int64

LL expmod(LL a, LL b, LL MOD) {
	if (b == 0) {
		return 1 % MOD;
	}
	LL v = expmod(a*a% MOD, b / 2, MOD);
	if (b & 1) {
		v = v * a % MOD;
	}
	return v;
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		printf("%d\n", (int)expmod(n, m, 1000));
	}
	return 0;
}