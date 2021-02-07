#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long
#define maxn 1000010

int nc[2][maxn], np[2][maxn];
int ncsize[2], npsize[2];

int c, p;

int main() {
	int i, j, x, idx;
	while(scanf("%d", &c) != EOF && c >= 0) {
		ncsize[0] = ncsize[1] = 0;
		npsize[0] = npsize[1] = 0;
		
		for(i = 0; i < c; ++i) {
			scanf("%d", &x);
			idx = x > 0 ? 0 : 1;
			nc[idx][ ncsize[idx]++ ] = x;		
		}
		scanf("%d", &p);
		for(i = 0; i < p; ++i) {
			scanf("%d", &x);
			idx = x > 0 ? 0 : 1;
			np[idx][ npsize[idx]++ ] = x;
		}
		for(i = 0; i < 2; ++i) {
			sort(nc[i], nc[i] + ncsize[i]);
			sort(np[i], np[i] + npsize[i]);		
		}
		ll ans = 0;
		for(i = ncsize[0]-1, j = npsize[0]-1; i >= 0 && j >= 0; --i, --j) {
			ans += (ll) nc[0][i] * np[0][j];
		}
		
		for(i = 0, j = 0; i < ncsize[1] && j < npsize[1]; ++i, ++j) {
			ans += (ll) nc[1][i] * np[1][j];
		}
	
		printf("%lld\n", ans);
		
	}	
	return 0;
} 
