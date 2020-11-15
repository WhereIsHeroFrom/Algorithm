#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100100
int a[MAXN];
char line[3000010];

void get() {
	int idx = 0, t = 0, s = 0;
	getchar();
	gets(line);

	while (line[idx]) {
		if (line[idx] >= '0' && line[idx] <= '9') {
			s = s * 10 + line[idx] - '0';
		}
		else {
			a[t++] = s;
			//printf("%d\n", s);
			s = 0;
		}
		++idx;
	}
	if (s) {
		a[t++] = s;
	}
}

int main() {
	int t;
	int n, i, cas = 0;

	scanf("%d", &t);
	while (t--) {

		scanf("%d", &n);
		get();
		sort(a, a + n);

		int ans = 0;
		for (i = n - 1; i >= 0; i -= 3) {
			ans += a[i];
			if (i)
				ans += a[i - 1];
		}
		printf("Case #%d: %d\n", ++cas, ans);
	}

	return 0;
}