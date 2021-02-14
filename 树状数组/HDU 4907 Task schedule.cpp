#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 200010
#define ll long long

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    while (x <= maxn) {
        c[x] += v;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

int a[MAXV];
int maxn;

int findans(int q) {
	int l = q, r = maxn;
	int ans = q;
	ll s = sum(q-1);
	
	while(l <= r) {
		int mid = (l +  r) >> 1;
		if( sum(mid) - s < mid - q + 1 ) {
			ans = mid;
			r = mid - 1;
		}	else {
			l = mid + 1;
		}
	}	
	return ans;
}

int main() {
	int t;
	int q, i, n, m;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		maxn = 0;
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if(a[i] > maxn) maxn = a[i];
		}
		++maxn;
		clear();
		for(i = 1; i <= n; ++i) {
			add(a[i], maxn, 1);
		}
		while(m--) {
			scanf("%d", &q);
			printf("%d\n", findans(q) );
		}
		
	}
	
	return 0;
} 
