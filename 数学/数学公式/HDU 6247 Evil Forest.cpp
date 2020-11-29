#include <iostream>

using namespace std;

int main() {
	int t = 0, cases;
	int v, n, x;
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d", &n);
		v = 0;
		while (n--) {
			scanf("%d", &x);
			v += (x + 9) / 10 + x;
		}
		printf("Case #%d: %d\n", ++t, v);
	}
	return 0;
}