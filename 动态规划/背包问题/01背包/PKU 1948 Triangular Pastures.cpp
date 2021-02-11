/*
	题意：给定 n(n <= 40) 个棒子，每个长度为 40，求围成三角形的最大值。
	
	题解：二维 0/1 背包
	用  dp[i][j] 代表组成 i 和 j 的两条边的情况是否存在，那么第三条边就是 sum-i-j,
	对三条边组成的三角形求最大面积。 
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
bool dp[1610][1610];
int a[50];

int main() {
	int i, j, k;
	
	while(scanf("%d", &n) != EOF) {
		for(i = 0;  i < n; ++i) {
			scanf("%d", &a[i]);
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		int sum = 0;
		for(i = 0; i < n; ++i) {
			sum += a[i];
			for(j = sum; j >= 0; --j) {
				for(k = sum - j; k >= 0; --k) {
					if(j >= a[i])
						dp[j][k] |= dp[j-a[i]][k];
					if(k >= a[i])
						dp[j][k] |= dp[j][k-a[i]];
				}
			}
		}
		
		int Max = -1;
		for(i = 0; i <= sum; ++i) {
			for(j = 0; j + i <= sum; ++j) {
				if(!dp[i][j]) continue;
				a[0] = i;
				a[1] = j;
				a[2] = sum - i - j;
				sort(a, a + 3);
				if(a[0] && a[1] && a[0] + a[1] > a[2]) {
					//printf("%d %d %d\n", a[0], a[1], a[2]);
					double cosa = a[0]*a[0] + a[1]*a[1] - a[2]*a[2];
					cosa /= 2 * a[0] * a[1];
					double c = sin( acos(cosa) );
					int v = (a[0] * a[1] * c * 50 + 1e-6);
					if(v > Max) Max = v;
				}
			}
		}
		printf("%d\n", Max);
	}
	
	return 0;
} 
