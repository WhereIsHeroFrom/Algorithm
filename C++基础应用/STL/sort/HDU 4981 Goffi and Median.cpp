#include <iostream>
#include <algorithm>

using namespace std;

int n, a[1100];

int main() {
	while(scanf("%d", &n) != EOF) {
		int s = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			s += a[i];
		}
		sort(a, a + n);
		int idx = (n+1)/2 - 1;
		if( s >= n * a[idx] ) {
			printf("NO\n");
		}else {
			printf("YES\n");
		}
		
	}
	
	return 0;
} 
