// HDU 2061
// 基础输入输出
// 加权平均
#include <iostream>

using namespace std;

double u, d;

int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		u = d = 0;
		while (n--) {
			char str[100];
			double c, s;
			scanf("%s %lf %lf", str, &c, &s);
			if (s < 60) u = -1;
			if (u >= 0) {
				u += c*s;
				d += c;
			}
		}
		if (u < 0) {
			printf("Sorry!\n");
		}
		else {
			printf("%.2lf\n", u / d);
		}

		if (t) {
			printf("\n");
		}
	}

	return 0;
}