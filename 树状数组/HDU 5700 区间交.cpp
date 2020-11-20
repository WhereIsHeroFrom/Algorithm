#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define LL __int64

int c[MAXN + 1];
int n;

int lowbit(int x) {
	return x & -x;
}

void add(int x, int v) {
	while (x <= n) {
		c[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int s = 0;
	while (x) {
		s += c[x];
		x ^= lowbit(x);
	}
	return s;
}


struct Interval {
	int l, r;

	void read() {
		scanf("%d %d", &l, &r);
	}
	bool operator<(const Interval& other) {
		return r < other.r;
	}
}I[MAXN];

int m;
LL s[MAXN];

int getk(int k) {
	int ans = -1;
	int l = 1, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (k <= sum(mid)) {
			ans = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return ans;
}

int main() {
	int i, j, k;
	while (scanf("%d %d %d", &n, &k, &m) != EOF) {
		for (i = 1; i <= n; ++i) {
			int v;
			scanf("%d", &v);
			s[i] = s[i - 1] + v;
			c[i] = 0;
		}
		for (i = 0; i < m; ++i) {
			I[i].read();
		}
		sort(I, I + m);

		LL maxSum = 0;
		for (i = 0; i < m; ++i) {
			add(I[i].l, 1);
		}
		for (i = 0; i < m; ++i) {
			int v = getk(k);
			if (v != -1) {
				if (v <= I[i].r) {
					LL Sum = s[I[i].r] - s[v - 1];
					if (Sum > maxSum) maxSum = Sum;
				}
			}
			else break;
			add(I[i].l, -1);
		}

		printf("%I64d\n", maxSum);
	}
	return 0;
}
/*
7 3 5
1 2 3 4 5 6 7
1 5
2 6
3 7
3 6
3 5
*/