// HDU 2057
// 进制转换：十进制和十六进制的互相转换

#include <iostream>
using namespace std;

char A[10000];
char B[10000];

__int64 CharGetVal(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	return c - 'A' + 10;
}

__int64 GetVal(const char *str) {
	int flag = 1, start = 0;
	if (str[0] == '-') {
		flag = -1;
		start = 1;
	}
	else if (str[0] == '+') {
		flag = 1;
		start = 1;
	}
	int i;
	__int64 s = 0;
	for (i = start; str[i]; ++i) {
		s = s * 16 + CharGetVal(str[i]);
	}
	return s * flag;
}

int sta[100];

int main() {
	int i;
	while (scanf("%s %s", A, B) != EOF) {
		__int64 sum = GetVal(A) + GetVal(B);
		if (sum < 0) {
			sum = -sum;
			printf("-");
		}
		else if (sum == 0) {
			printf("0\n");
			continue;
		}
		sta[0] = 0;
		while (sum) {
			sta[++sta[0]] = sum % 16;
			sum /= 16;
		}
		for (i = sta[0]; i > 0; --i) {
			if (sta[i] >= 10) printf("%c", sta[i] - 10 + 'A');
			else printf("%d", sta[i]);
		}
		puts("");

	}
	return 0;
}