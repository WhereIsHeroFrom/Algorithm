// HDU 2025
// ASCII 码的基础应用
#include <iostream>
using namespace std;

char str[200];

char lowwer(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 'a';
	}
	return c;
}

bool isLargerthan(char a, char b) {
	return a > b;
}

bool isEqual(char a, char b) {
	return a == b;
}

int main() {
	int i;
	while (scanf("%s", str) != EOF) {
		int idx = 0;
		for (i = 1; str[i]; ++i) {
			if (isLargerthan(str[i], str[idx])) {
				idx = i;
			}
		}
		for (i = 0; str[i]; ++i) {
			printf("%c", str[i]);
			if (isEqual(str[i], str[idx])) {
				printf("(max)");
			}
		}
		puts("");
	}
}