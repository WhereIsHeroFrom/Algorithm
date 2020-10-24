// HDU 2051
// 计算机进制转换

#include <iostream>
using namespace std;

int sta[100];

int main() {
	int n, i;
	while (scanf("%d", &n) != EOF) {
		sta[0] = 0;
		while (n) {
			sta[++sta[0]] = (n & 1);
			n >>= 1;
		}
		for (i = sta[0]; i > 0; --i) printf("%d", sta[i]);
		puts("");
	}
	return 0;
}