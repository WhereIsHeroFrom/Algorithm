#include <iostream>

using namespace std;

int a[110], sum[110];
int n, m;

int ABS(int x) {
	return x < 0 ? -x : x;
}

int main() {
	int t;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum[i] = (sum[i-1] ^ a[i]);
		}
		scanf("%d", &m);
		while(m--) {
			int x;
			scanf("%d", &x);
			int T = -1;
			int L = -1;
			
			for(int i = n; i >= 1; --i) {
				for(int j = 1; j + i - 1 <= n; ++j) {
					int v = sum[j+i-1] ^ sum[j-1];
					int ans = ABS(v - x);
					if( ans < T || T == -1) {
						T = ans;
						L = i;
					}
				}
			}
			printf("%d\n", L);
		}
		puts("");
	}
	
	return 0;
} 
