// HDU 2042
// 数学递推：递推公式 a[i] = 2*(a[i-1] - 1)
#include <iostream>
using namespace std;
#define LL __int64

int main() {
	int t, i;
	int n;
	scanf("%d", &t);
	while (t--) {
		int pre = 3;
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			pre = 2 * (pre - 1);
		}
		printf("%d\n", pre);
	}
}