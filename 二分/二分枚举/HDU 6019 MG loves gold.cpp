#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

int a[MAXN], b[MAXN], hashv[MAXN];
int n, m;
int cases;

void unique() {
	m = 1;
	int i;
	for (i = 1; i < n; ++i) {
		if (b[i] != b[m - 1]) {
			b[m++] = b[i];
		}
	}
}

int binary(int v) {
	int l = 0, r = m - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (b[mid] == v) return mid;
		if (b[mid] < v) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
}

int main() {
	int t;
	int i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b, b + n);
		unique();
		++cases;
		int ans = 1;
		hashv[binary(a[0])] = cases;
		for (i = 1; i < n; ++i) {
			int v = binary(a[i]);
			//printf("%d %d\n", v, m);
			if (hashv[v] == cases) {
				++ans;
				hashv[v] = ++cases;
			}
			else {
				hashv[v] = cases;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}