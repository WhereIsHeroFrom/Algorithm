#include <iostream>
#include <cmath>
using namespace std;

#define LL long long

LL Exp(LL a, LL n){
	LL ans = 1;
	while (n){
		if (n & 1) ans = ans*a;
		a = a*a;
		n >>= 1;
	}
	return ans;
}

int main() {
	LL K;
	int k;
	while (scanf("%d", &k) != EOF && k) {
		K = k;
		int ans = 0;
		for (int Z = 2;; ++Z) {
			if (Exp(2, Z) > K) {
				break;
			}

			for (LL X = 1;; ++X) {
				if (Exp(X, Z) > k) {
					break;
				}
				LL Ylow = X + 1, YHigh = (int)(pow(k, 1.0 / Z) + 1);
				while (Ylow <= YHigh) {
					LL Y = (Ylow + YHigh) / 2;
					LL al = Exp(X, Z) + Exp(Y, Z) + X * Y * (LL)Z;
					if (al == k) {
						ans++;
						break;
					}
					else if (al < k) {
						Ylow = Y + 1;
					}
					else {
						YHigh = Y - 1;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*
2147483644
121
9
53
6
*/