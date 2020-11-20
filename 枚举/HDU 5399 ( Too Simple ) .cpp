#include <iostream>

using namespace std;

#define MOD 1000000007
#define MAXN 110
#define LL __int64

int A[MAXN][MAXN];
int n, m;
LL f[MAXN];
int hashv[MAXN];

int main() {
	int i, j;
	f[0] = 1;
	for (i = 1; i < MAXN; ++i) {
		f[i] = f[i - 1] * i % MOD;
	}

	while (scanf("%d %d", &n, &m) != EOF) {
		int cnt = 0;
		bool flag = true;

		for (i = 1; i <= m; ++i) {
			for (j = 1; j <= n; ++j) {
				scanf("%d", &A[i][j]);
				if (A[i][j] == -1) {
					++cnt;
					break;
				}
			}
			memset(hashv, 0, sizeof(hashv));
			if (flag && j > n) {
				for (j = 1; j <= n; ++j) {
					if (A[i][j] < 1 || A[i][j] > n || hashv[A[i][j]]) {
						flag = false;
						break;
					}
					++hashv[A[i][j]];

				}
			}
		}
		if (!flag) {
			printf("0\n");
			continue;
		}
		LL ans = 0;
		if (cnt == 0) {
			for (i = 1; i <= n; ++i) {
				int x = i;
				for (j = m; j >= 1; --j) {
					x = A[j][x];
				}
				if (x != i) {
					break;
				}
			}
			if (i == n + 1) {
				++ans;
			}
		}
		else {
			ans = 1;
			for (i = 0; i < cnt - 1; ++i)
				ans = ans * f[n] % MOD;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}