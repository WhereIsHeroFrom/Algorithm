// HDU 2009
// 数学函数 sqrt 求平方根
#include <iostream>
using namespace std;

double n, m;

int main() {
	int x, y;
	while (scanf("%lf %lf", &n, &m) != EOF && n) {
		double sum = 0;
		while (m--) {
			sum += n;
			n = sqrt(n);
		}
		printf("%.2lf\n", sum);
	}
	return 0;
}