#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int a[100010];

int main() {
	while(scanf("%d %d", &n, &m) != EOF && (n||m) ) {
		for(int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a, a + n);
		for(int i = 0; i < m && i < n; ++i) {
			if(i) printf(" ");
			printf("%d", a[n-1-i]);
		}
		puts("");
		
	} 
	return 0;	
} 
