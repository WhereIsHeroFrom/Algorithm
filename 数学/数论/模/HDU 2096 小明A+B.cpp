// HDU 2096
// 数论： 取模的基本性质
// 注意一定要分别取模后相加再取模，因为A和B分别在int32范围，相加就可能超int32；

#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		int A, B;
		scanf("%d %d", &A, &B);
		printf("%d\n", (A % 100 + B % 100) % 100);
	}

	return 0;
}
