// HDU 2095
// Œª‘ÀÀ„£∫ “ÏªÚ

#include <iostream>

using namespace std;

int n;

int main() {
	int i;
	while (scanf("%d", &n) != EOF && n) {
		int v = 0;
		for (i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			v ^= x;
		}
		printf("%d\n", v);
	}
	return 0;
}