// HDU 2029
// Ã¶¾Ù
#include <iostream>
#include <cstring>
using namespace std;

char str[100000];

int main() {
	int t, i;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		int len = strlen(str);
		for (i = 0; i < len / 2; ++i) {
			if (str[i] != str[len - 1 - i]) break;
		}
		if (i == len / 2) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
}