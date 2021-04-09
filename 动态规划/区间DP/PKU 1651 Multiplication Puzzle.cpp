#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int maxn = 110;
const int inf = -1;
const int maxv = 1e9;

int dp[maxn][maxn];
int a[maxn];

void init() {
	memset(dp, inf, sizeof(dp));
}

int dfs(int l, int r) {
	if(l + 1 == r) {
		return 0;
	}
	int &val = dp[l][r];
	if(val != inf) {
		return val;
	}
	val = maxv;
	
	for(int k = l + 1; k < r; ++k) {
		int now = dfs(l, k) + dfs(k, r) + a[l] * a[k] * a[r];
		val = min(val, now);
	} 
	return val;
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		printf("%d\n", dfs(1, n) );	
	}
	return 0;
} 
