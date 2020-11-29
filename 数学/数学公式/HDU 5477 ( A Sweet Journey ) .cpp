#include <iostream>
#include <cstring>
using namespace std;

int n, A, B, L;

int main() {
	int t;
	int i, cases = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &n, &A, &B, &L);
		int pre = 0;
		int v = 0, ans = 0;
		for (i = 0; i < n; i++) {
			int l, r;
			scanf("%d %d", &l, &r);
			if (l - pre > 0) {
				v += B * (l - pre);
			}
			v -= A * (r - l);
			if (v < ans) ans = v;
			pre = r;
		}
		printf("Case #%d: %d\n", ++cases, -ans);
	}
	return 0;
}