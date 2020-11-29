// HDU 2012
// ËØÊýÉ¸Ñ¡
#include <iostream>
using namespace std;

#define MAXN 65536

int n, m;
bool f[MAXN];

bool isPrime(int v) {
	if (v <= 0 || v >= MAXN) {
		return false;
	}
	return !f[v];
}

int func(int x) {
	return x*x + x + 41;
}

int main() {
	int i, j;
	f[1] = 1;
	for (i = 2; i < MAXN; ++i) {
		if (!f[i]) {
			for (j = i * i; j < MAXN && j >= 0; j += i) {
				f[j] = 1;
			}
		}
	}

	int x, y;
	while (scanf("%d %d", &x, &y) != EOF && (x || y)) {
		for (i = x; i <= y; ++i) {
			if (!isPrime(func(i))) {
				break;
			}
		}
		if (i == y + 1) {
			printf("OK\n");
		}
		else {
			printf("Sorry\n");
		}
	}
	return 0;
}