// HDU 2090
// double 的四舍五入处理

#include <iostream>

using namespace std;

char str[100000];
double a, b;

int main() {
	double s = 0;
	while (scanf("%s %lf %lf", str, &a, &b) != EOF) {
		s += a*b;
	}
	printf("%.1lf\n", s);
	return 0;
}