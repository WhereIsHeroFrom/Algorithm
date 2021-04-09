#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define maxn 110
#define inf 0x3f3f3f3f

int fmax[maxn][maxn], fmin[maxn][maxn];
int val[maxn];
char op[maxn];

void init() {
	memset(fmax, inf, sizeof(fmax));
	memset(fmin, inf, sizeof(fmin));	
}

int fval[maxn];

int dfs(int l, int r) {
	if(l == r) {
		fmax[l][r] = fmin[l][r] = val[l];
		return val[l];
	}	
	int &vmax = fmax[l][r];
	if(vmax != inf) {
		return vmax;
	}
	int &vmin = fmin[l][r];
	
	vmax = -100000000;
	vmin =  100000000;
	
	for(int k = l; k < r; ++k) {
		dfs(l, k);
		dfs(k+1, r);
		
		if(op[k + 1] == '+') {
			vmax = max(vmax, fmax[l][k] + fmax[k+1][r] );
			vmin = min(vmin, fmin[l][k] + fmin[k+1][r] );
		} else {
			vmax = max(vmax, fmax[l][k] * fmax[k+1][r] );
			vmax = max(vmax, fmin[l][k] * fmin[k+1][r] );
			
			vmin = min(vmin, fmin[l][k] * fmax[k+1][r] );
			vmin = min(vmin, fmin[l][k] * fmin[k+1][r] );
			vmin = min(vmin, fmax[l][k] * fmax[k+1][r] );
			vmin = min(vmin, fmax[l][k] * fmin[k+1][r] );
		}
	}
	return vmax; 
}

int main() {
	int n;
	while(scanf( "%d", &n ) != EOF) {
		for(int i = 0; i < n; ++i) {
			char str[10];
			scanf("%s %d", str, &val[i]);
			op[i] = (str[0] == 't' ? '+' : '*');
			
			val[i+n] = val[i];
			op[i+n] = op[i];
		}
		init();
		int maxv = -1000000000;
		for(int i = 0; i < n; ++i) {
			fval[i] = dfs(i, i + n - 1);
			maxv = max(maxv, fval[i]);
		}
		printf("%d\n", maxv);
		int flag = 0;
		for(int i = 0; i < n; ++i) {
			if(fval[i] == maxv) {
				if(flag) {
					printf(" ");
				}
				flag = 1;
				printf("%d", i+1);
			}
		}
		puts("");
		
	}
	return 0;
} 
