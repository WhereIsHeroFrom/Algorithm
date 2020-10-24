// HDU 2006
// Œª‘ÀÀ„≈–∂œ∆Ê≈º–‘
#include <iostream>
using namespace std;

__int64 sum;

int main() {
	int i;
	int n, v;
	while (scanf("%d", &n) != EOF) {
		sum = 1;
		while (n--) {
			scanf("%d", &v);
			if (v&1)
				sum *= (__int64)v;
		}
		printf("%I64d\n", sum);
	}
	return 0;
}