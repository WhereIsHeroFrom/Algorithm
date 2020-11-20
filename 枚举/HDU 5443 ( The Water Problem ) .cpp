#include <iostream>

using namespace std;

#define MAXN 1010

int a[MAXN];
int n;

int main() {
	int t;
	int i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int q;
		scanf("%d", &q);
		while (q--) {
			int l, r;
			scanf("%d %d", &l, &r);
			int v = a[l];
			for (i = l + 1; i <= r; ++i) {
				if (a[i] > v) v = a[i];
			}
			printf("%d\n", v);
		}
	}
	return 0;
}