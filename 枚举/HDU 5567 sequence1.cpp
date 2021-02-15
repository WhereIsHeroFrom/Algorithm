#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 110;

int a[MAXN];

int main() {
	int n, b, c, i, j;
	
	while(scanf("%d %d %d", &n, &b, &c) != EOF) {
		for(i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		int cnt = 0;
		for(i = 0; i < n; ++i) {
			for(j = i+1; j < n; ++j) {
				if( abs(a[i] - a[j]) % b == c ) {
					++cnt;
				}
			}
		}
		printf("%d\n", cnt);
	}	
	
	return 0;
} 
