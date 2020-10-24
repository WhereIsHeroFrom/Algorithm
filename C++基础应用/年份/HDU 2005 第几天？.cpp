// HDU 2005
// 考察闰年、平年、日期统计的概念；
#include <iostream>
using namespace std;

int monthday[] = { 0,
31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31
};
int sumday[13];
char str[100];
int y, m, d;

int main() {
	int i;
	while (scanf("%s", str) != EOF) {
		sscanf(str, "%4d/%2d/%2d", &y, &m, &d);
		if (y % 4 == 0 && y % 100 || y % 400 == 0) {
			// 闰年
			monthday[2] = 29;
		}
		else {
			monthday[2] = 28;
		}
		sumday[0] = 0;
		for (i = 1; i <= 12; ++i) {
			sumday[i] = sumday[i - 1] + monthday[i];
		}
		int ans = sumday[m - 1] + d;
		printf("%d\n", ans);
	}
	return 0;
}
