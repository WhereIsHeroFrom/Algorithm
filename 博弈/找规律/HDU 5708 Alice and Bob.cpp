#include <iostream>

using namespace std;

int Q, k, m, n;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &Q, &k);
		while (Q--) {
			scanf("%d %d", &n, &m);
			if (n > m) {
				int tmp = n; n = m; m = tmp;
			}
			bool ans = false;
			if (n % (k + 1) == 0) {
				ans = true;
			}
			else if (k == 1) {
				ans = (m % 2 == 0);
			}
			else {
				ans = ((n - n / (k + 1)) + m) & 1;
			}
			printf("%s\n", ans ? "Alice" : "Bob");
		}
	}
	return 0;
}