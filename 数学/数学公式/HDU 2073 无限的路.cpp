// HDU 2073 
// 数学：平面坐标系

#include <iostream>
#include <cmath>

using namespace std;

double sqr(double x) {
	return x * x;
}

double dist(double x1, double y1, double x2, double y2) {
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

int main() {
	int n;
	int x1, y1, x2, y2;
	scanf("%d", &n);

	while (n--) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		if (x1 + y1 > x2 + y2) {
			int tmpx = x1; x1 = x2; x2 = tmpx;
			int tmpy = y1; y1 = y2; y2 = tmpy;
		}

		double ans = 0;
		while (x1 + y1 < x2 + y2) {

			// (x1,y1) -> (x1+y1, 0)
			ans += sqrt(2.0) * y1;
			x1 = x1 + y1;    y1 = 0;

			// (x1, 0) -> (0, x1 + 1)
			ans += dist(x1, 0, 0, x1 + 1);
			y1 = x1 + 1;     x1 = 0;
		}
		ans += dist(x1, y1, x2, y2);

		printf("%.3lf\n", ans);

	}
	return 0;
}