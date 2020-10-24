// HDU 2099
// 数论：整除的性质

#include <iostream>

using namespace std;

int ans[200];

int main() {
	int a, b;
	int i;
	while (scanf("%d %d", &a, &b) != EOF && (a || b)) {
		ans[0] = 0;
		for (i = 0; i < 100; ++i) {
			if ((a * 100 + i) % b == 0) {
				ans[++ans[0]] = i;
			}
		}
		for (i = 1; i <= ans[0]; ++i) {
			if (i > 1) {
				printf(" ");
			}
			printf("%02d", ans[i]);
		}
		puts("");
	}


	return 0;

}