#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXM 110

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 10010
#define ll long long
#define MOD 123456789

ll c[MAXM][MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int n, int x, int maxn, ll v) {
    while (x <= maxn) {
        c[n][x] += v;
        if(c[n][x] >= MOD) {
        	c[n][x] %= MOD;
		}
        x += lowbit(x);
    }
}

ll sum(int n, int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[n][x];
        if(s >= MOD) {
        	s %= MOD;
		}
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************


int a[MAXV], asize;

int getIndex(int v) {
	int l = 0, r = asize - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(a[mid] == v) {
			return mid + 1;
		}else if(v > a[mid]) {
			l = mid + 1;
		}else {
			r = mid - 1;
		}
	}
}

int getValue(int idx) {
	return a[ idx - 1 ];
}

void sortIt() {
	sort(a, a + asize);
	int tmpsize = 0;
	for(int i = 0; i < asize; ++i) {
		if(!i || a[i] != a[tmpsize - 1]) {
			a[ tmpsize++ ] = a[i];
		}
	}
	asize = tmpsize;
}

/*
	dp[n][m] 代表以第 n 个元素结尾，序列长度为 m 的方案数； 
	则 dp[0][0] = 1;
	
	dp[n][m] = sum{ i < n | dp[i][m-1] };
	
*/

int val[MAXV];
ll dp[MAXV][MAXM];

int main() {
    int n, m, i, j;
    
    while (scanf("%d %d", &n, &m) != EOF) {
        clear();
		asize = 0;
		
		val[0] = -1; 
		a[asize++] = val[0];
        
		for(i = 1; i <= n; ++i) {
        	scanf("%d", &val[i]);
        	a[asize++] = val[i]; 
		}
		sortIt();
		
		add(0, 1, asize, 1);
		ll s = 0;
		for(i = 1; i <= n; ++i) {
			int index = getIndex(val[i]);
			
			for(j = 1; j <= m; ++j) {
				dp[i][j] = sum(j-1, index-1);
				add(j, index, asize, dp[i][j]);				
			}
			s += dp[i][m];
			if(s >= MOD) s %= MOD;
		}
		printf("%d\n", (int)s);
    }

    return 0;
}

