#include <iostream>
#include <cstring>

using namespace std;

#define ll long long
const int MAXN = 100010;
const int BASE = 50000;

int has[MAXN], a[MAXN];
int pos;
int n, m;

int main() {
	int i;
	while(scanf("%d %d", &n, &m) != EOF) {
		memset(has, 0, sizeof(has));
		
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if(m == a[i]) {
				pos = i;
			}
		}	
		int small = 0, big = 0;	
		for(i = pos; i >= 1; --i) {
			if(a[i] < m) {
				++small;
			}else if(a[i] > m) {
				++big;
			}
			++ has[small - big + BASE];
		}
		ll ans = 0; 
		small = 0, big = 0; 
		for(i = pos; i <= n; ++i) {
			if(a[i] < m) {
				++small;
			}else if(a[i] > m) {
				++big;
			}
			ans += has[big - small + BASE];
		}
		printf("%lld\n", ans);
	}
	return 0;
} 

/*
9 5
1 5 7 2 6 3 8 4 9
5

7 6
7 3 2 6 8 9 4

3 2 
2 3 1

*/
