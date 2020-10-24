// HDU 2013
// สýังฬโ: a[i] = 2*(a[i-1] +1)
#include <iostream>
using namespace std;


int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		unsigned int v = 1;
		while (--n) {
			v = v * 2 + 2;
		}
		printf("%u\n", v);
	}
	return 0;
}