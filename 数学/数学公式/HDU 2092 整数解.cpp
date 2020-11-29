// HDU 2092
// 数学：二次方程求根

#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-8

int check(int a, int b) {

	int pre = a*a - 4.0 * b;
	if (pre < 0) return false;

	int sq = (int)(sqrt(pre) + eps);

	if (sq*sq == pre) {
		if ((a + sq) % 2 == 0 || (a - sq) % 2 == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}

int main() {
	int n, m;

	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		printf("%s\n", check(n, m) ? "Yes" : "No");
	}

	return 0;
}
