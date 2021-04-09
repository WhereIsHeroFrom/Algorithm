#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define maxn 210
const int mod = 1e9+7;
int dp[maxn][maxn];
int a[maxn], b[maxn];

void init() {
	memset(dp, -1, sizeof(dp));
}

int dfs(int l, int r) {
	if(l > r) {
		return 0;
	}
	int &val = dp[l][r];
	if(val != -1) {
		return val;
	}
	val = INT_MAX;
	for(int i = l; i <= r; ++i) {
		int lv = dfs(l, i-1);
		int rv = dfs(i+1, r);
		int ans = lv + rv + a[i] + b[l-1] + b[r+1];
		val = min(val, ans);
	}
	return val;
}

int main() {
	int n; 
	int t, cas = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &b[i]);
		} 
		b[0] = b[n+1] = 0;
		dfs(1, n);
		printf("Case #%d: %d\n", ++cas, dp[1][n]);
	}
	return 0;
} 
