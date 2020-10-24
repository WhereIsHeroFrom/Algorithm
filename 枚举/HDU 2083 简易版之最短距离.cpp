// HDU 2083
// Ã¶¾Ù

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int n;
int a[1000];

int main() {
	int t, i, j;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		int val = -1;
		for (i = 0; i < n; ++i) {
			int ans = 0;
			for (j = 0; j < n; ++j) {
				ans += abs(a[i] - a[j]);
			}
			if (ans < val || val == -1) {
				val = ans;
			}
		}
		printf("%d\n", val);
	}

	return 0;
}