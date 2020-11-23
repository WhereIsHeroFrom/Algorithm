#include <iostream>
using namespace std;

#define MAXN 201000

int n, k;
int A[MAXN];
int m;

bool check(int m, int large) {
	int seg = n / m;
	int maxv = -1;
	int cnt = 0;
	int sum = 0;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] > maxv) {
			maxv = A[i];
		}
		cnt++;
		if (cnt == seg) {
			sum += maxv;
			cnt = 0;
			maxv = -1;
			tot++;
			if (sum > large) return true;
			if (tot == m) return false;
		}
	}
	return false;
}

int solve() {
	int sum = 0;
	for (m = 0; m < n; m++) {
		sum += A[m];
	}
	if (sum <= k) return -1;

	for (m = 1; m <= n; m++) {
		if (m*m > n) break;
		if (check(m, k)) {
			return m;
		}
	}
	int inv;
	for (inv = m; inv >= 1; inv--) {
		int l = 1 + n / (inv + 1);
		int r = n / inv;
		//printf("%d %d\n", l, r);
		if (check(r, k)) {
			int ll = l, rr = r;
			int ans = -1, mid;
			while (ll <= rr) {
				mid = (ll + rr) >> 1;
				if (check(mid, k)) {
					rr = mid - 1;
					ans = mid;
				}
				else {
					ll = mid + 1;
				}
			}
			return ans;
		}
	}
	return n;
}

int main() {
	int i;
	while (scanf("%d %d", &n, &k) != EOF && (n >= 0 || k >= 0)) {
		for (i = 0; i < n; i++) {
			scanf("%d", &A[i]);
		}
		printf("%d\n", solve());
	}
	return 0;
}
/*
12 500
7 100 7 101 100 100 9 100 100 110 110 89
*/