#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 8010
#define BASE 8000

int n;
int val[MAXN], findval[MAXN];
int sum[MAXN];
int hashCnt[2][2 * MAXN], hashCase[2][2 * MAXN], cases;

int getIndex(int v) {
	int l = 1, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (v == findval[mid]) {
			return mid;
		}
		else if (v > findval[mid]) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return -1;
}

int main() {
	int i, j;
	while (scanf("%d", &n) != EOF) {
		for (i = 1; i <= n; ++i) {
			scanf("%d", &val[i]);
			findval[i] = val[i];
		}
		sort(findval + 1, findval + n + 1);
		for (i = 1; i <= n; ++i) {
			val[i] = getIndex(val[i]);
		}

		// Ã¶¾ÙÆðµã
		for (i = 1; i <= n; i++) {
			int ans = 0;
			sum[0] = BASE;
			for (j = 1; j <= n; ++j) {
				if (i == j) {
					sum[j] = sum[j - 1];
				}
				else
					sum[j] = sum[j - 1] + (val[j] < val[i] ? -1 : 1);
			}
			++cases;

			for (j = 0; j < i; ++j) {
				int mod = (j & 1);
				int v = sum[j];
				if (hashCase[mod][v] < cases) {
					hashCase[mod][v] = cases;
					hashCnt[mod][v] = 0;
				}
				++hashCnt[mod][v];
			}

			for (j = i; j <= n; ++j) {
				int mod = (j & 1);
				int v = sum[j];
				ans += hashCase[1 - mod][v] < cases ? 0 : hashCnt[1 - mod][v];
			}

			if (i > 1) printf(" ");
			printf("%d", ans);
		}
		puts("");
	}
	return 0;
}

/*
13
9 8 0 1 2 4 21 7 56 6 3 99 101
ans = [ 1 2 1 3 5 7 3 11 2 10 1 2 1 ]

*/