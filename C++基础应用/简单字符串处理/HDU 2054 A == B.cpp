// HDU 2054
// 细节题: 考虑正负号、前导零、浮点数的尾零

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define MAXN 1000010

char A[100000], B[100000];
char tmp[MAXN];

void filter_leadingzero(char *str) {
	int i = 0, c = 0;
	int idx = 0;

	while (str[i]) {
		if (str[i] >= '1' && str[i] <= '9' || str[i] == '.') break;
		if (str[i] == '0') ++c;
		++i;
	}

	if (c) {
		while (str[i]) {
			if (str[i] >= '1' && str[i] <= '9' || str[i] == '.') break;
			if (str[i] == '0') {

			}
			else {
				tmp[idx++] = str[i];
			}
		}

		while (str[i]) {
			tmp[idx++] = str[i];
			++i;
		}
		tmp[idx] = '\0';

		strcpy(str, tmp);
	}

}

void filter_tailzero(char *str) {
	int i, len = strlen(str);
	for (i = 0; i < len; ++i) {
		if (str[i] == '.') {
			break;
		}
	}
	if (i < len) {
		i = len - 1;
		while (i >= 0) {
			if (str[i] == '0') --i;
			else break;
		}
		if (i < 0) {
			i = 0;
			str[0] = '0';
			str[1] = '\0';
		}
		else {
			if (str[i] == '.') {
				if (i == 0) {
					str[0] = '0';
					str[1] = '\0';
				}
				else {
					str[i] = '\0';
				}
			}
			else {
				str[i + 1] = '\0';
			}
		}

	}
}

void filter_postionsign(char *str) {
	if (str[0] == '+') {
		strcpy(tmp, &str[1]);
		strcpy(str, tmp);
	}
}

int main() {
	while (scanf("%s %s", A, B) != EOF) {
		filter_leadingzero(A); //printf("%s\n", A);
		filter_leadingzero(B); //printf("%s\n", B);

		filter_tailzero(A); //printf("%s\n", A);
		filter_tailzero(B); //printf("%s\n", B);

		filter_postionsign(A); //printf("%s\n", A);
		filter_postionsign(B); //printf("%s\n", B);

		printf("%s\n", strcmp(A, B) == 0 ? "YES" : "NO");
	}
	return 0;
}

// .4    0.4
// 00001 00000000000001
// +1212132 1212132
// +1212132 1212132.000000
