#include <iostream>

using namespace std;

int ans[] = { 1, 2, 16, 32 };

int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		if (n >= 4) {
			printf("%d\n", 4);
		}
		else {
			printf("%d\n", ans[n]);
		}
	}


	return 0;
}