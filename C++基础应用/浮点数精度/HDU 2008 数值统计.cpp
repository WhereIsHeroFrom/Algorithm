// HDU 2008
// 浮点数相等判断
#include <iostream>
using namespace std;
#define eps 1e-9

int n;
int sum[3];

int main() {
	int x, y;
	while (scanf("%d", &n) != EOF && n) {
		sum[0] = sum[1] = sum[2] = 0;
		while (n--) {
			double v;
			scanf("%lf", &v);
			if (fabs(v) < eps) {
				++sum[1];
			}
			else if (v < 0) {
				++sum[0];
			}
			else {
				++sum[2];
			}
		}
		printf("%d %d %d\n", sum[0], sum[1], sum[2]);
	}
	return 0;
}