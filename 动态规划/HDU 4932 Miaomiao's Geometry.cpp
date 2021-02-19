#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
int a[55];
bool dp[55][2];

int main() {
	int i, j;
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		
		for(i = 1; i <= n; ++i ) {
			scanf("%d", &a[i]);
		}
		double Max = 0;
		sort(a + 1, a + n + 1);
		
		int tmp = 1;
		for(i = 2; i <= n; ++i) {
			if(a[i] != a[i-1]) {
				a[++tmp] = a[i];
			}
		}
		n = tmp;
		
		for(i = 2; i <= n; ++i) {
			double LL = a[i] - a[i-1];
			int cnt = 0;
			for(double L = LL; cnt < 2; L /= 2, ++cnt) {
				dp[1][0] = dp[1][1] = 1;
				
				for(j = 2; j <= n; ++j) {
					dp[j][0] = 0;
					
					if(L <= a[j] - a[j-1]) {
						dp[j][0] |= dp[j-1][0];
					}	
					if( fabs(a[j] - a[j-1] - L) < 1e-8 || a[j] - a[j-1] >= 2*L ) {
						dp[j][0] |= dp[j-1][1];
					}
					
					dp[j][1] = dp[j-1][0];
					if( L <= a[j] - a[j-1]) {
						dp[j][1] |= dp[j-1][1];
					}
					
				}
				
				if( dp[n][0] || dp[n][1] ) {
					if(L > Max) {
						Max = L;
					}
				}				
			}

		}
		printf("%.3lf\n" , Max);
		
	}	
	
	return 0;
} 

/*
1
7
-6 -1 0 6 13 15 19
*/
