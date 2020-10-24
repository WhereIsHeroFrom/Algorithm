// HDU 2055
// ASCII 码的简单应用

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

char str[100];
int val;

int getval(char c) {
	if (c >= 'a' && c <= 'z') {
		return -(c - 'a' + 1);
	}
	return c - 'A' + 1;
}

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%s %d", str, &val);
		printf("%d\n", val + getval(str[0]));
	}

	return 0;
}