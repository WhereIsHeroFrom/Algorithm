#include <iostream>

using namespace std;

int main() {
	int k, p;
	int i, j;
	while (scanf("%d %d", &k, &p) != EOF) {
		bool win;
		if (p == 2) {
			win = (k & 1);
		}
		else {
			win = (k / (p - 1)) & 1;
		}
		printf("%s\n", win ? "YES" : "NO");
	}
	return 0;
}