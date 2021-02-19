#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 6;

int has[maxn], stk[maxn];
int a[maxn];

bool process() {
	int i;
	int x[4];
	
	// Secondly , Grandpa Shawn take the first one and the last one , sum them up as his scores.
	int s = a[ stk[0] ] + a[ stk[maxn-1] ];
	
	for(int j = 1; j < maxn - 1; ++j) {
		x[j-1] = a[ stk[j] ];
	}
	sort(x, x + 4);
	
	if( s > x[1] + x[2] + x[3] ) {
		return true;
	}
	return false;
}

bool dfs(int dep) {
	if(dep == maxn) {
		if( process() ) {
			return true;
		}
		return false;
	}
	for(int i = 0; i < maxn; ++i) {
		if(!has[i]) {
			has[i] = 1;
			stk[ dep ] = i;
			if( dfs(dep + 1) ) {
				return true;
			}
			has[i] = 0;
		}
	}
	return false;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		for(int i = 0; i < maxn; ++i) {
			scanf("%d", &a[i]);
		}
		memset(has, 0, sizeof(has));
		
		if( dfs(0) ) {
			printf("Grandpa Shawn is the Winner!\n");
		}else {
			printf("What a sad story!\n");
		}
		
	}
	
	return 0;
} 
