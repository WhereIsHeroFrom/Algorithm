// HDU 2056
// 计算几何：矩形面积交

#include <iostream>
#include <cmath>
#include <cstring>

struct Point {
	double x, y;
	void Scanf() {
		scanf("%lf %lf", &x, &y);
	}
}A, B, C, D;

double Min(double a, double b) {
	return a < b ? a : b;
}

double Max(double a, double b) {
	return a > b ? a : b;
}


struct Intval {
	double min, max;

	double intersect(const Intval& o) const {
		double a = Max(min, o.min);
		double b = Min(max, o.max);
		if (a < b) {
			return b - a;
		}
		return 0;
	}
}X[2], Y[2];



int main() {
	while (scanf("%lf %lf", &A.x, &A.y) != EOF) {
		B.Scanf();
		C.Scanf();
		D.Scanf();

		X[0].min = Min(A.x, B.x);
		X[0].max = Max(A.x, B.x);

		X[1].min = Min(C.x, D.x);
		X[1].max = Max(C.x, D.x);

		Y[0].min = Min(A.y, B.y);
		Y[0].max = Max(A.y, B.y);

		Y[1].min = Min(C.y, D.y);
		Y[1].max = Max(C.y, D.y);

		double ans = X[0].intersect(X[1]) * Y[0].intersect(Y[1]);
		printf("%.2lf\n", ans);
	}
	return 0;
}