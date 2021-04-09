#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define maxn 110
const int mod = 1e9+7;
int dp[maxn][maxn];
int a[maxn];
int cc[maxn*2][maxn*2], p[maxn*2]; 
char c[maxn];
void init() {
	memset(dp, -1, sizeof(dp));
}

int dfs(int l, int r) {
	if(l == r) {
		return a[l];
	}
	int &val = dp[l][r];
	if(val != -1) {
		return val;
	}
	val = 0;
	for(int i = l; i < r; ++i) {
		ll lef = dfs(l, i);
		ll rig = dfs(i+1, r);
		int sum = 0; 
		if(c[i] == '+') {
			sum = (lef * p[r-i-1]  + rig * p[i-l]) % mod;
			
		}else if(c[i] == '-') {
			sum = (lef * p[r-i-1]  - rig * p[i-l]) % mod;
			if(sum < 0) {
				sum += mod;
			}
		}else if(c[i] == '*') {
			sum = (ll)lef * rig % mod;
		}
		val +=  (ll)sum * cc[ r-l-1 ][i-l] % mod;
		if(val >= mod) {
			val %= mod;
		}
	}
	return val;
}

int main() {
	cc[0][0] = 1;
	p[0] = 1;
	for(int i = 1; i <= 200; ++i) {
		for(int j = 0; j <= i; ++j) {
			if(!j) cc[i][j] = 1;
			else if(j == i){
				cc[i][j] = 1;
			}else { 
				cc[i][j] = (cc[i-1][j] + cc[i-1][j-1]) % mod;
			}
		}
		p[i] = (ll)p[i-1] * i % mod;
	}
	int n; 
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		scanf("%s", c);
		dfs(0, n-1);
		printf("%d\n", dp[0][n-1]);
	}
	return 0;
} 
