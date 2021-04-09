#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 1010;
const int inf = -1;
#define ll long long

ll f[maxn][maxn][2];

void init() {
	memset(f, inf, sizeof(f));
}

int S, n, a[maxn];

ll dfs(int l, int r, int pos) {
	if(l == r) {
		return abs(S - a[l]) * n;
	}
	
	int stalecnt = n - (r - l);
	ll &val = f[l][r][pos];
	if(val != inf) {
		return val;
	}
	val = (ll)INT_MAX * 10000000;
	if(pos == 0) {
		val = min(val, (ll)(a[l+1]-a[l])*stalecnt + dfs(l+1, r, 0));
		val = min(val,   (ll)(a[r]-a[l])*stalecnt + dfs(l+1, r, 1));
	}else {
		val = min(val, (ll)(a[r]-a[r-1])*stalecnt + dfs(l, r-1, 1));
		val = min(val,   (ll)(a[r]-a[l])*stalecnt + dfs(l, r-1, 0));
	}
	
	return val;
}

int main() {
	int i;
	while( scanf("%d %d", &n, &S) != EOF ) {
		init();
		for(i = 0; i < n; ++i) {
			scanf("%d", a + i);
		}
		sort(a, a + n);
		ll ans = min(dfs(0, n-1, 0), dfs(0, n-1, 1));
		printf("%lld\n", ans);
	}	
	return 0;
}
