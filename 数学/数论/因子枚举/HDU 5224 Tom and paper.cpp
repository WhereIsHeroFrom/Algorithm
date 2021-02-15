#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int t, n, i;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		int Max = -1;
		int x = sqrt(n + 1.0);
		for(i = 1; i <= x; ++i) {
			if(n % i == 0) {
				int ans = 2 *(i + n/i);
				if(Max == -1 || ans < Max) Max = ans;
			}
		}
		printf("%d\n", Max);
	}
	return 0;
} 
