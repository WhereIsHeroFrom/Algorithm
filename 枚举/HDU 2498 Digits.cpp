/*
题意：
x[i] = x[i-1]的十进制表示的数字个数

给定 x[0] 求最小的 x[i] == x[i-1]

题解：
枚举
*/


#include <iostream>
#include <cstring>
using namespace std;

char   str[1000100];
char str_s[1000100];

int val(char *str) {
	return strlen(str);
}

int countBy(int v) {
	if (v == 0) {
		return 1;
	}
	int c = 0;
	while (v) {
		v /= 10;
		c++;
	}
	return c;
}

void conv(char *s, int v, int len) {
	int i, top = 0;
	while (v) {
		s[top++] = (v % 10) + '0';
		v /= 10;
	}
	if (top < len) {
		for (i = top; i < len; ++i) s[i] = '0';
		top = len;
	}
	s[top] = '\0';

	for (i = 0; i < top / 2; ++i) {
		char c = s[i];
		s[i] = s[top - 1 - i];
		s[top - 1 - i] = c;
	}

}

int main() {
	int i;
	while (scanf("%s", str) != EOF) {
		if (!strcmp(str, "END")){
			break;
		}
		int x0 = val(str);

		conv(str_s, x0, strlen(str));

		//puts(str_s);

		if (!strcmp(str_s, str)) {
			printf("1\n");
			continue;
		}
		int x1;
		for (i = 2;; ++i) {
			x1 = countBy(x0);
			if (x1 == x0) break;
			x0 = x1;
		}
		printf("%d\n", i);
	}

	return 0;
}