/*
	题意：k(k <= 40) 个物品中，最多选择 n 个，并且价值不能超过 m(m <= 10^9)，
	求能够达到的最大价值；
	
	题解：搜索 + 剪枝
	 
*/

#include <iostream>
#include <algorithm> 
using namespace std;

const int maxn = 110;
#define ll long long

int a[maxn];
ll sum[maxn];
int n, k, W;
ll MAXANS;

void dfs(int now, int need, ll nowW) {
	
	if(nowW > W) {
		// 1. 可行性剪枝 
		return ;
	}
	if(nowW > MAXANS) {
		// 更新最优解 
		MAXANS = nowW;
	}
	
	if(MAXANS == W) {
		// 2. 找到最优解剪枝 
		return ;
	}
	
	if(need == 0) {
		return ;
	}
	
	ll maxSum = nowW + sum[now + need < k ? now + need : k] - sum[now];
	if( maxSum <= MAXANS ) {
		// 2. 最大的剩余和 小于等于 当前最优解，剪枝！ 
		return ;
	}
	
	if( maxSum <= W) {
		// 3. 最大的剩余和 小于等于 最大值，剪枝！ 
		MAXANS = maxSum;
		return;
	} 
	
	for(int i = now + 1; i <= k; ++i) {
		dfs(i, need-1, nowW + a[i]);
	}
}

int main() {
	int i;
	while(scanf("%d %d", &n, &W) != EOF) {
		 
		scanf("%d", &k);
		for(i = 1; i <= k; ++i) {
			scanf("%d", &a[i]);
			a[i] = -a[i];
		}		
		sort(a + 1, a + k + 1);
		for(i = 1; i <= k; ++i) {
			a[i] = -a[i]; // printf("%d\n", a[i]);
			sum[i] = sum[i-1] + a[i];
		}
		MAXANS = 0;
		dfs(0, n, 0);
		printf("%lld\n", MAXANS);
	}
	return 0;
} 

/*
3 116
40
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30 
31 32 33 34 35 36 37 38 39 40

*/
