// HDU 2017
// C++ ASCIIÂë ³£Ê¶
#include <iostream>
#include <algorithm>
using namespace std;

int n;
char str[110200];

int main() {
	int t;
	int i, c;
	scanf("%d", &t);
	while (t--) {
		c = 0;
		scanf("%s", str);
		for (i = 0; str[i]; ++i) {
			if (str[i] >= '0' && str[i] <= '9') ++c;
		}
		printf("%d\n", c);
	}
	return 0;
}