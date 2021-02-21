#include <iostream>

using namespace std;

#define MAXN 10010
#define MAXC 110
const int inf = -1e9;
const int init = 0;

int dp[MAXN][MAXC];
int dp0[MAXC][MAXC];

int c[MAXC], g[MAXC];

int Max(int a, int b) {
	return a > b ? a : b;
}

void zeroOne(int& cnt, int cap, int *c, int *w) {
	int i, j;
	
	for(i = 0; i <= cap; ++i) {
		dp0[0][i] = i ? inf : init;
	}
	int cap0w = inf; 
	for(i = 1; i <= cnt; ++i) {
		for(j = 0; j <= cap; ++j) {
			dp0[i][j] = dp0[i-1][j];
			if(j >= c[i])
				dp0[i][j] = Max(dp0[i][j], dp0[i-1][ j - c[i] ] + w[i]);
		}
		if(c[i] == 0) {
			if(cap0w == inf) {
				cap0w = 0;
			}
			cap0w += w[i];
		}
	}
	int count = 0;
	if(cap0w != inf) {
		++count;
		c[ count ] = 0;
		w[ count ] = cap0w;
	}
	for(i = 1; i <= cap; ++i) {
		if(dp0[cnt][i] >= 0) {
			++count;
			c[ count ] = i;
			w[ count ] = dp0[cnt][i];
		}
	}
	cnt = count;
}

int main() {
	int i, j, k, cap;
	int n, m, t;
	
	while(scanf("%d %d", &n, &t) != EOF) {
		for(i = 0; i <= t; ++i) {
			dp[0][i] = i ? inf : init;
		}
		k = 0;
		for(i = 1; i <= n; ++i) {
			int m, s;
			scanf("%d %d", &m, &s);
			for(j = 1; j <= m; ++j) {
				scanf("%d %d", &c[j], &g[j]);
			}
			if(s == 2) {
				for(j = 1; j <= m; ++j) {
					for(cap = 0; cap <= t; ++cap) {
						// 当前 j 号物品不选 
						dp[k+j][cap] = dp[k+j-1][cap];
						// 当前 j 号物品选择 
						if(cap >= c[j]) {
							dp[k+j][cap] = Max(dp[k+j][cap], dp[k+j-1][ cap - c[j] ] + g[j] ); 
						}
					}
				}
				k += m;
				continue;
			}else if(s == 0) {
				zeroOne(m, t, c, g);				
				/*for(j=1; j <= m; ++j) {
					printf("(%d,%d)\n", c[j], g[j]);
				}*/
			}

			for(cap = 0; cap <= t; ++cap) {
				dp[k+1][cap] = s==1 ? dp[k][cap] : inf;
			}
			for(j = 1; j <= m; ++j) {
				for(cap = 0; cap <= t; ++cap) { 
					if(cap >= c[j]) {
						dp[k+1][cap] = Max(dp[k+1][cap], dp[k][ cap - c[j] ] + g[j] ); 
					}
				}
			}
			
			
			k += 1;
		}
		
		int ans = inf;
		for(i = 1; i <= t; ++i) {
			ans = Max(ans, dp[k][i]);
		}
	 	if( ans < 0 ) {
	 		ans = -1;
		}
		printf("%d\n", ans);
	}
	
	return 0;
} 

/*
2 3

2 1
2 11
3 1111

2 0
1 0
2 1
*/
