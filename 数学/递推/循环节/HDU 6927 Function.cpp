/*
	模拟找规律，循环节
*/

#include <iostream>

using namespace std;

#define LL long long

int f(int x) {
	if (!x) {
		return 0;
	}

	int xcopy = x;
	LL p = 10;
	LL ans = 1;

	while (xcopy) {
		ans = ans * (x % p) % (x + 1);
		p *= 10;
		xcopy /= 10;
	}
	return ans;
}
int G[1000010];

int main() {
	int t;
	int n, m;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		G[1] = f(n);
		LL ans = G[1];
		for (int i = 2; i <= m; ++i) {
			G[i] = f(G[i - 1]);
			if (G[i] == G[i - 1]) {
				ans += (LL)(m-i+1) * (LL)G[i];
				break;
			}
			ans += G[i];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}