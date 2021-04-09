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
int c[maxn][maxn];

void init() {
	memset(f, inf, sizeof(f));
}

int n, color[maxn];

ll dfs(int l, int r) {
	if(l >= r) {
		return 1;
	}
	
	int &val = f[l][r];
	if(val != inf) {
		return val;
	}
	val = 0;
	for(int k = l; k <= r; ++k) {
		if(k==l || k==r || color[k-1] == color[k+1]) {
			ll ans = 1;
			ans = ans * c[r-l][k-l] % mod;
			ans = ans * dfs(l, k-1) % mod;
			ans = ans * dfs(k+1, r) % mod;
			val = (val + ans) % mod;
			
		}
	}
	return val;
}

int main() {
	int i;
	
	c[0][0] = 1;
	for(int i = 1; i < maxn; ++i) {
		for(int j = 0; j < maxn; ++j) {
			if(!j) {
				c[i][j] = 1;
			} else {
				c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
			}
		}
 	}
	
	while( scanf("%d", &n) != EOF ) {
		init();
		for(i = 1; i <= n; ++i) {
			scanf("%d", color + i);
		}
		if(n == 1) {
			printf("%d\n", 1);
			continue;
		}
		
		color[0] = color[2];
		color[n+1] = color[n-1];
		
		int ans = dfs(1, n);
		printf("%d\n", ans);
	}	
	return 0;
}
