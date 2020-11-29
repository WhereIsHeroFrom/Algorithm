// HDU 2050
// ¼òµ¥ÊýÑ§
// 2*n*n - n + 1

#include <iostream>
using namespace std;

int n;
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("%d\n", 2 * n*n - n + 1);
	}
}