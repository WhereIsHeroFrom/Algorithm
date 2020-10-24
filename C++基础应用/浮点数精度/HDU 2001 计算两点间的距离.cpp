// HDU 2001
// double 精度高，不能用 float
#include <iostream>
#include <cmath>
using namespace std;

double x[2], y[2];
double sqr(double x) {
	return x * x;
}

int main() {
	while (scanf("%lf %lf %lf %lf", &x[0], &y[0], &x[1], &y[1]) != EOF) {
		printf("%.2lf\n", sqrt(sqr(x[0] - x[1]) + sqr(y[0] - y[1])));
	}
	return 0;
}