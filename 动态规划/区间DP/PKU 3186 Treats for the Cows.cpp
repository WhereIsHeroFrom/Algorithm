#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define maxn 2010
int dp[maxn][maxn];
int a[maxn], n;
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
	val = 0;
	int now = n - (r-l);
	int lv = dfs(l+1, r);
	int rv = dfs(l, r-1);
	val = max( lv + now * a[l], rv + now * a[r]);
	return val;
}

int main() {
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		dfs(1, n);
		printf("%d\n", dp[1][n]);
	}
	return 0;
} 
