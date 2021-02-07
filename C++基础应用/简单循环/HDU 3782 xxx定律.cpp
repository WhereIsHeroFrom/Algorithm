#include <iostream>

using namespace std;

int main() {
	int n;
	while(scanf("%d", &n) != EOF && n) {
		int step = 0;
		while(n != 1){
			if(n & 1) {
				n = (3*n + 1) / 2;
			}else {
				n = n / 2;
			}
			++step;
		}
		printf("%d\n", step);
	}
	
	return 0;
} 
