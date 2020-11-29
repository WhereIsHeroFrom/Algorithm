#include <iostream>
#include <cstring>
using namespace std;

bool has[100000];

int main() {
	int n;
	while(scanf("%d", &n) != EOF && n) {
		memset(has, 0, sizeof(has));
		has[n] = 1;
		int c = 1;
		while(1) {
			n *= n;
			n /= 100;
			n %= 10000;
			if(has[n]) {
				break;
			}
			has[n] = 1;
			++c;
		}
		printf("%d\n", c);
	}
	
	return 0;
} 
