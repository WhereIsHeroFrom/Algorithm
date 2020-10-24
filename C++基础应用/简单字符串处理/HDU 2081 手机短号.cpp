// HDU 2081
// ¼òµ¥×Ö·û´®´¦Àí

#include <iostream>

using namespace std;

char str[10000];


int main() {
	int t, i;
	scanf("%d", &t);

	while (t--) {
		scanf("%s", str);
		printf("6");
		for (i = 6; i < 11; ++i) {
			printf("%c", str[i]);
		}
		puts("");
	}
	return 0;
}