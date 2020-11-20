#include <iostream>

using namespace std;

int n;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		n--;
		printf("1");
		while (n--) printf("0");
		puts("");
	}
	return 0;
}