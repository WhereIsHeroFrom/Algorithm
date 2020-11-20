#include <iostream>

using namespace std;

#define MAXL 100010
#define LL __int64

int n;
int a[MAXL], b[MAXL], pos[MAXL];
int v[MAXL];

int main() {
	int t;
	int i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			pos[a[i]] = i;
		}
		for (i = 1; i <= n; ++i) {
			scanf("%d", &b[i]);
			v[i] = 0;
		}
		int ans = 0;
		for (i = 1; i <= n; ++i) {
			if (!v[i]) {
				if (a[i] == b[i]) {
					++ans;
				}
				else {
					int cnt = 0;
					int p = i;
					while (!v[p]) {
						//printf("->%d", a[p]);
						v[p] = 1;
						p = pos[b[p]];
						cnt++;
					}
					ans += (cnt - 1);
					//puts("");
				}
			}
		}
		printf("%d\n", ans);

	}
	return 0;
}