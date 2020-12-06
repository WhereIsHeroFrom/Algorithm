#include <iostream>

using namespace std;

int main() {
	int a, b, c;
	while (scanf("%d %d %d", &a, &b, &c) != EOF) {
		int bottles = a + b;
		int ans = 0;
		while (bottles >= c) {
			ans += bottles / c;
			bottles = bottles / c + bottles % c;
		}
		printf("%d\n", ans);
	}

	return 0;
}