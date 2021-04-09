#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 2010;
const int inf = -1;
#define ll int

ll f[maxn][maxn];

void init() {
	memset(f, inf, sizeof(f));
}

int S, n, a[maxn], c[maxn];

ll dfs(int l, int r) {
	if(l > r) {
		return 0;
	}
	if(l == r) {
		return 1;
	}
	
	ll &val = f[l][r];
	if(val != inf) {
		return val;
	}
	val = 0;
	if(a[l] == a[r]) {
		val = max(val, dfs(l+1, r-1) + 2 * );
	}
	val = max(val, dfs(l+1, r));
	val = max(val, dfs(l, r-1));

	
	return val;
}

int main() {
	int i;
	while( scanf("%d", &n) != EOF && n ) {
		init();
		int t = 0;
		for(i = 1; i <= n; ++i) {
			scanf("%d", &x);
			if(t == 0) {
				a[++t] = x;
				c[t] = 1;
			}else if(x == a[t]) {
				++c[t];
			}else {
				a[++t] = x;
				c[t] = 1;
			}
		}
		for(i = 1; i <= t; ++i) {
			a[t+i] = a[i];
			c[t+i] = c[i];
		}
		int ans = dfs(1, 2*t);
		printf("%d\n", ans );
	}	
	return 0;
}

/*
10
1 1 1 1 1 2 2 2 2 2
*/
