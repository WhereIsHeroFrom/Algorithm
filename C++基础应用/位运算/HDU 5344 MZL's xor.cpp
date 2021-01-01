#include <iostream>

using namespace std;

#define LL long long

int n, m, z, l;
LL A;

int main() {
	int t, i;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d %d %d", &n, &m, &z, &l);
		A = 0;
		int ans = 0;
		for (i = 2; i <= n; ++i) {
			A = (A * m + z) % l;
			ans ^= (2 * A);
		}
		printf("%d\n", ans);
	}
	return 0;
}