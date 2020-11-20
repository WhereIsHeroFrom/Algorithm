// HDU 2097
// 数学进制的基本知识

#include <iostream>

using namespace std;

int getval(int val, int b) {
	int ans = 0;
	while (val) {
		ans += val % b;
		val /= b;
	}
	return ans;
}
int main() {
	int n;
	int i;
	while (scanf("%d", &n) != EOF && n) {
		if (getval(n, 10) == getval(n, 12) && getval(n, 10) == getval(n, 16)) {
			printf("%d is a Sky Number.\n", n);
		}
		else {
			printf("%d is not a Sky Number.\n", n);
		}

	}

	return 0;
}