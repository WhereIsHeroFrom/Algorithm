#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define ll long long
#define maxn 310
const int mod = 1e9+7;
int dp[maxn][maxn];
int valid[maxn][maxn];
int a[maxn], d[maxn];

void init() {
	memset(valid, 0, sizeof(valid));
	memset(dp, -1, sizeof(dp));
}

int dfs(int l, int r) {
	if(l > r) {
		return 0;
	}
	if(l == r) {
		return 0;
	}

	int &val = dp[l][r];
	if(val != -1) {
		return val;
	}
	val = 0;
	// 切分 
	for(int i = l; i <= r; ++i) {
		int lv = dfs(l, i);
		int rv = dfs(i+1, r);
		int ans = lv + rv;
		val = max(val, ans);
	}
	
	if(val == r-l+1) {
		return val;
	}
	
	if(r - l >= 2) {
		for(int k = l+1; k < r; ++k) {
			// 不满足公差出现 
			if(!valid[l][k] || !valid[k][r]) {
				continue;
			}
			// 不满足公差相等
			if(a[l] + a[r] != a[k] * 2) {
				continue;
			} 
			if(k == l+1 || dfs(l+1, k-1) == k-l-1 ) {
				
				if(k == r-1 || dfs(k+1, r-1) == r-k-1 ) {
					return val = r - l + 1;
				}
			}
		}
	} 
	if(valid[l][r]) {
		if(l + 1 == r || dfs(l+1, r-1) == r-l-1) {
			return val = r - l + 1;
		} 
	}
	
	return val;
}

bool canfind(int dsize, int *d, int val) {
	int l = 0, r = dsize - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(val == d[mid]) {
			return true;
		}
		if(val > d[mid]) {
			l = mid + 1;
		}else {
			r = mid - 1;
		}
	}
	return false;
}

int main() {
	int n, m; 
	int t, cas = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		for(int i = 0; i < m; ++i) {
			scanf("%d", &d[i]);
		}
		sort(d, d + m);
		
		for(int i = 1; i <= n; ++i) {
			for(int j = i + 1; j <= n; ++j) {
				valid[i][j] = canfind(m, d, a[j] - a[i]);
			}
		}

		int ans = dfs(1, n);
		printf("%d\n", ans);
	}
	return 0;
} 
