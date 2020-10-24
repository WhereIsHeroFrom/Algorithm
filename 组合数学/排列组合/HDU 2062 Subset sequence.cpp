// HDU 2062
// 组合数学：组合，子集，递归
// 子集数的递推式 P[n] = n*(P[n-1] + 1);
// 注意 m 要用 __int64

#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 30

LL A[MAXN][MAXN];
LL P[MAXN];
bool has[MAXN];
int sta[MAXN + 1];

int main() {
	int i, j;
	for (i = 0; i < MAXN; ++i) {
		P[i] = 0;
		for (j = 0; j < MAXN; ++j) {
			int v = i, cnt = j;
			A[i][j] = 1;
			while (cnt--) {
				A[i][j] *= v;
				--v;
			}
			if (j)
				P[i] += A[i][j];
		}
		//printf("%d %I64d\n", i, P[i]);
	}

	int n;
	__int64 m;
	while (scanf("%d %I64d", &n, &m) != EOF) {
		memset(has, 0, sizeof(has));
		int nown = n;
		sta[0] = 0;
		while (m >= 1) {
			// 一直减 (P[nown - 1] + 1)，并且计数，减了几次
			int cnt = 0;
			while (m > 0) {
				m -= (P[nown - 1] + 1);
				++cnt;
			}
			m += P[nown - 1];
			for (i = 1; i <= n; ++i) {
				if (has[i]) continue;
				--cnt;
				if (cnt == 0) {
					break;
				}
			}
			sta[++sta[0]] = i;
			has[i] = true;
			--nown;
		}

		for (i = 1; i <= sta[0]; ++i) {
			if (i > 1) {
				printf(" ");
			}
			printf("%d", sta[i]);
		}
		puts("");
	}

	return 0;
}