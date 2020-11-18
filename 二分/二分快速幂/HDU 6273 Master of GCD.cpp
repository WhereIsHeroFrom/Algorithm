#include <iostream>
#include <cstring>
using namespace std;

#define MOD 998244353
#define LL long long
#define MAXN 100010

LL power(LL a, LL b) {
	if (b == 0) {
		return 1 % MOD;
	}
	LL tmp = power(a*a%MOD, b / 2);
	if (b & 1) {
		tmp = tmp * a % MOD;
	}
	return tmp;
}

int cnt[4][MAXN];
int n, m, l, r, x;

int main() {
	int t, i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		memset(cnt, 0, sizeof(cnt));

		while (m--) {
			scanf("%d %d %d", &l, &r, &x);
			if (l <= r) {
				++cnt[x][l];
				--cnt[x][r + 1];
			}
		}
		LL s2 = 0, s3 = 0;
		LL minS2 = -1, minS3 = -1;
		for (i = 1; i <= n; ++i) {
			s2 += cnt[2][i];
			s3 += cnt[3][i];
			if (s2 < minS2 || minS2 == -1)minS2 = s2;
			if (s3 < minS3 || minS3 == -1)minS3 = s3;
		}
		LL l = power(2, minS2) * power(3, minS3) % MOD;
		printf("%lld\n", l);
	}
	return 0;
}