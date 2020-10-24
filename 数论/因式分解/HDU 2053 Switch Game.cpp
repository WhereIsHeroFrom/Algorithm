// HDU 2053
// 数论：一个数的因子数是奇数还是偶数
// 素数筛选

#include <iostream>
using namespace std;

#define MAXN 100100

bool f[MAXN];
int p[MAXN];

int main() {
	int i, j;
	f[1] = 1;
	p[0] = 0;
	for (i = 2; i < MAXN; ++i) {
		if (!f[i]) {
			p[++p[0]] = i;
			for (j = i * i; j < MAXN && j >= 0; j += i) {
				f[j] = 1;
			}
		}
	}
	int n;
	while (scanf("%d", &n) != EOF) {
		int ans = 1;
		for (i = 1; i <= p[0]; ++i) {
			if (n % p[i] == 0) {
				int c = 1;
				n /= p[i];
				while (n % p[i] == 0) {
					n /= p[i];
					++c;
				}
				ans *= (c + 1);
			}
		}
		if (ans & 1) {
			printf("1\n");
		}
		else {
			printf("0\n");
		}
	}
	return 0;
}