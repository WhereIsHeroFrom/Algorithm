#include <iostream>
#include <cstring>
using namespace std;

struct K {
	int code;
	int cnt;
}f[10];

int has[300], col[300];

int main() {
	int t, i;
	int n, k;
	char ch[10];
	int val;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &k);
		int ans = 0;
		for (i = 0; i < n; ++i) {
			scanf("%s %d", ch, &val);
			f[i % k].code = ch[0];
			f[i % k].cnt = val;

			int maxv = (i < k) ? i : k - 1;
			int c = 0;

			memset(has, 0, sizeof(has));
			memset(col, 0, sizeof(col));

			for (int j = 0; j <= maxv; ++j) {
				if (!has[f[j].code]) {
					has[f[j].code] = 1;
					++c;
				}
				col[f[j].code] += f[j].cnt;
			}

			for (int j = 0; j < 300; ++j) {
				if (col[j] == 5) {
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}