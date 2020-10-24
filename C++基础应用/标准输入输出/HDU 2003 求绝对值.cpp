// HDU 2003
// 浮点数求绝对值函数 fabs 的应用
#include <iostream>
#include <cmath>
using namespace std;

double R;

int main() {
	while (scanf("%lf", &R) != EOF) {
		printf("%.2lf\n", fabs(R));
	}
	return 0;
}