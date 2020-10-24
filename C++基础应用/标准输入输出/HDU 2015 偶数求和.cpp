// HDU 2015
// C++整数除法取下整
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int s, cnt;
int a[200], b[200];

int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF) {
		b[0] = 0;
		s = 0, cnt = 0;
		for (i = 1; i <= n; ++i) {
			a[i] = 2 * i;
			s += a[i];
			if (++cnt == m) {
				b[++b[0]] = s / cnt;
				cnt = s = 0;
			}
		}
		if (cnt) {
			b[++b[0]] = s / cnt;
			cnt = s = 0;
		}
		for (i = 1; i <= b[0]; ++i) {
			if (i > 1) {
				printf(" ");
			}
			printf("%d", b[i]);
		}
		puts("");

	}
	return 0;
}