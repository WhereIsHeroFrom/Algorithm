// HDU 2039
// 数学
// 三角形两边之和大于第三边
// STL sort 函数应用
// 注意浮点数精度问题，用 <= 代替 > 判断

#include <iostream>
#include <algorithm>
using namespace std;

double a[3];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%lf %lf %lf", &a[0], &a[1], &a[2]);
		sort(a, a + 3);
		printf("%s\n", a[0] + a[1] <= a[2] ? "NO" : "YES");
	}
	return 0;
}