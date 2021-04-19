#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define maxn 210
const int inf = -1;
int f[2][maxn][maxn];
int a[maxn], sum[maxn];

void init() {
	memset(f, -1, sizeof(f));
}

void dfs(int l, int r) {
	if(l == r) {
		f[0][l][l] = f[1][l][l] = 0;
		return ;
	}
	int &minval = f[0][l][r];
	int &maxval = f[1][l][r];	
	if(minval != -1) {
		return ;
	}
	
	minval = INT_MAX;
	maxval = INT_MIN;
	
	for(int i = l; i < r; ++i) {
		dfs(l, i);
		dfs(i+1, r);
		minval = min(minval, f[0][l][i] + f[0][i+1][r] + sum[r] - sum[l-1]);
		maxval = max(maxval, f[1][l][i] + f[1][i+1][r] + sum[r] - sum[l-1]);	
	}
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[n+i] = a[i];
		}
		for(int i = 1; i <= 2*n;++i) {
			sum[i] = sum[i-1] + a[i];
		}
		int minv = INT_MAX, maxv = 0;
		for(int i = 1; i <= 1; ++i) {
			dfs(i, i + n - 1);
			minv = min(minv, f[0][i][i+n-1]);
			maxv = max(maxv, f[1][i][i+n-1]);
		}
		printf("%d\n%d\n", minv, maxv);
	}
	return 0;
} 

/*
5
7 15 9 18 5
*/
