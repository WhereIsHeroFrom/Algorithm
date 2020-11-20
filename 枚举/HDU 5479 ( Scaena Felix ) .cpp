#include <iostream>
#include <cstring>
using namespace std;

char str[1010];

int main() {
	int t;
	int i, j;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		int len = strlen(str);
		int ans = -1;

		for (i = 0; i <= len; i++) {
			int v = 0;
			for (j = 0; j < len; j++) {
				char c;
				if (j < i) {
					c = ')';
				}
				else {
					c = '(';
				}
				v += c == str[j] ? 0 : 1;
			}
			if (v < ans || ans == -1) {
				ans = v;
			}
		}
		if (len == 1) ans = 0;

		printf("%d\n", ans);
	}
	return 0;
}