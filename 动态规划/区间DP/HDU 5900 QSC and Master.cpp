#include <iostream>
#include <cstring>

using namespace std;

#define LL __int64
#define MAXN 310
const int inf = -1;

int n;
int key[MAXN], v[MAXN];
bool fit[MAXN][MAXN];
LL dp[MAXN][MAXN];
LL sum[MAXN][MAXN];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

LL dfs(int l, int r) {
	if(l > r) {
		return 0;
	}
	if(l == r) {
		return 0;
	}
	LL &val = dp[l][r];
	if(val != inf) {
		return val;
	}
	val = 0;
	for(int k = l; k <= r; ++k) {
		val = max(val, dfs(l, k) + dfs(k+1, r) );
	}
	if(fit[l][r]) {
		if( dfs(l+1, r-1) == sum[l+1][r-1] ) {
			val = max(val, sum[l+1][r-1] + v[l] + v[r] );
		}
	}
	return val;
}

int main() {
	int t;
	int i, j, k;

	scanf("%d", &t);

	while (t--) {
		memset(dp, inf, sizeof(dp));
		memset(fit, 0, sizeof(fit));
		memset(sum, 0, sizeof(sum));

		scanf("%d", &n);

		for (i = 1; i <= n; ++i) {
			scanf("%d", &key[i]);
		}
		for (i = 1; i <= n; ++i) {
			scanf("%d", &v[i]);
		}

		for (i = 1; i <= n; ++i) {
			fit[i][i] = 0;
			sum[i][i] = v[i];
			for (j = i + 1; j <= n; ++j) {
				fit[i][j] = gcd(key[i], key[j]) > 1;
				sum[i][j] = sum[i][j - 1] + v[j];
			}
		}
		
		LL ans = dfs(1, n);

		printf("%I64d\n", ans);
	}

	return 0;
}
/*
10
5
2 4 6 8 10
1 2 3 4 5

5
2 4 6 8 10
5 4 3 2 1

6
2 6 3 6 5 10
11 1 9 1 1 1

9
2 4 8 3 6 9 12 4 4
8 1 9 9 9 8 10 1 1111

10
9 7 2 3 4 4 3 2 7 2
1 1 1 1 1 1 1 1 1 1

9
5 5 2 3 3 2 6 6 5
0 1 1 1 1 1 1 1 1

8
7 3 3 5 2 2 5 7
1 1 1 1 1 1 1 1
*/
