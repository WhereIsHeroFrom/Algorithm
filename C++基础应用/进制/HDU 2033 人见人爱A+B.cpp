// HDU 2033
// 计算机数字进制转换的应用
// 时钟可以看成是 60进制

#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64

LL a[2][3];
LL val[3];

int main() {
	int t;
	int i, k;
	scanf("%d", &t);
	while (t--) {
		for (k = 0; k < 2; ++k) {
			for (i = 0; i < 3; ++i) {
				scanf("%I64d", &a[k][i]);
			}
		}

		LL carry = 0;
		for (i = 2; i >= 0; --i) {
			LL tot = (carry + a[0][i] + a[1][i]);
			carry = tot / 60;
			val[i] = tot;
			if (i) val[i] %= 60;
		}
		for (i = 0; i < 3; ++i) {
			if (i) printf(" ");
			printf("%I64d", val[i]);
		}
		puts("");
	}

	return 0;
}