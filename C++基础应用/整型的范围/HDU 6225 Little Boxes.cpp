#include <iostream>
using namespace std;

#define ull unsigned long long
#define MAX (((ull)1)<<62) 


int main() {
	int t;
	ull a, b, c, d;
	scanf("%d", &t);
	while (t--) {
		scanf("%llu %llu %llu %llu", &a, &b, &c, &d);
		if (a == MAX && b == MAX && c == MAX && d == MAX) {
			printf("18446744073709551616\n");
		}
		else
			printf("%llu\n", a + b + c + d);
	}
	return 0;
}