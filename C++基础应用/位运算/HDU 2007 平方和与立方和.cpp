// HDU 2007
// Œª‘ÀÀ„≈–∂œ∆Ê≈º–‘
#include <iostream>
using namespace std;

__int64 sum[2];

int main() {
	int x, y;
	while (scanf("%d %d", &x, &y) != EOF) {
		if (x > y) {
			__int64 tmp = x;
			x = y;
			y = tmp;
		}
		sum[0] = sum[1] = 0;
		for (__int64 i = x; i <= y; ++i) {
			if (i & 1) {
				sum[1] += i*i*i;
			}
			else {
				sum[0] += i*i;
			}
		}
		printf("%I64d %I64d\n", sum[0], sum[1]);
	}
	return 0;
}