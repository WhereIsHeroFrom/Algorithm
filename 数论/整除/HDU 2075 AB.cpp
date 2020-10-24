// HDU 2075
// 数论，记得判断 B 为 0 的情况

#include <iostream>
#include <cstring>
using namespace std;

int main() {

	int a, b;
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &a, &b);

		if (b == 0 || a % b) {
			printf("NO\n");
		}
		else {
			printf("YES\n");
		}
	}

	return 0;
}