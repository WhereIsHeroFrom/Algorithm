#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 110;
const int inf = -1;
const int mod = 1e9 + 7; 
#define ll long long

int f[maxn][maxn];

void init() {
	memset(f, inf, sizeof(f));
}
int n, a[maxn], sum[maxn];

ll dfs(int l, int r) {
	
	if(l > r) {
		return 0;
	}
	
	int &val = f[l][r];
	if(val != inf) {
		return val;
	}
	val = INT_MAX;
	
	for(int k = 1; k <= r-l+1; ++k) {
		int ans = (k-1) * a[l];
		ans += dfs(l+1, l+k-1);
		ans += dfs(l+k, r);
		ans += k * (sum[r] - sum[l+k-1]);
		val = min(val, ans);
	}

	return val;
}

int main() {
	int i;
	int t, cas = 0;
	scanf("%d", &t);
	while( t-- ) {
		
		scanf("%d", &n);
		init();
		for(i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum[i] = sum[i-1] + a[i];
		}

		int ans = dfs(1, n);
		printf("Case #%d: %d\n", ++cas, ans);
	}	
	return 0;
}
