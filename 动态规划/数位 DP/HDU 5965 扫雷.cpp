#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10010;
const int mod  = 100000007; 
#define ll long long

int n;
int f[maxn][4][4];
char str[maxn];

int dfs(int depth, int n, int precode, int code) {
	if(depth == n) {
		return 1;
	}
	int &s = f[depth][precode][code];
	if(s != -1) {
		return s;
	}
	s = 0;
	
	int tot = 0;
	tot += (precode >> 1) & 1;
	tot += precode & 1;
	tot += (code >> 1) & 1;
	tot += code & 1;
	int maxv = (depth == n-1) ? 1 : 4; 
	for(int i = 0; i < maxv; ++i) {
		int nextup = (i >> 1) & 1;
		int nextdown = i & 1;
		if( tot + nextup + nextdown == str[depth] - '0') {
			s += dfs(depth+1, n, code, i);
		} 
	}
	s %= mod; 
	return s; 
}

int main() {
    ll a, b;
    int t;
    scanf("%d", &t);
    while (t--) {
		scanf("%s", str);
		int len = strlen(str);
		memset(f, -1, sizeof(f));
		printf("%d\n", ( dfs(0, len, 0, 0) + dfs(0, len, 0, 1) + dfs(0, len, 0, 2) + dfs(0, len, 0, 3) ) % mod );
    }
    return 0;
}

