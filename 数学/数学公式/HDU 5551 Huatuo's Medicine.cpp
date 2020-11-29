#include <iostream>

using namespace std;

int main() {
	int n, t, cases = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("Case #%d: %d\n", ++cases, 2 * n - 1);
	}
	return 0;
}