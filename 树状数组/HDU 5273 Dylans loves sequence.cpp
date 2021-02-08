#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 10010
#define ll int

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
int b[MAXV], bsize;

void sortIt() {
	sort(b, b + bsize);
	int btmpsize = 0;
	for(int i = 0; i < bsize; ++i) {
		if(!i || b[i] != b[btmpsize-1]) {
			b[btmpsize++] = b[i];
		}
	}
	bsize = btmpsize;
}

int getIndex(int now) {
	int l = 0, r = bsize - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(now == b[mid]) {
			return mid + 1;
		}else if(now > b[mid]) {
			l = mid + 1;
		}else {
			r = mid - 1;
		}
	}
}

struct Interval {
	int L, R;
	int idx;
	
	void read(int i) {
		scanf("%d %d", &L, &R);
		//L = rand() % 1000 + 1;
		//R = rand() % 1000 + 1;
		if(L > R) {
			swap(L, R);
		}
		idx = i;
	}
	
	bool operator < (const Interval& I) const {
		if(R != I.R)
			return R < I.R;
		return L > I.L;
	}
}I[100010];

ll s[100010], ans[100010];
 
int main() {
	int i, j;
	int n, Q;
	
	while(scanf("%d %d", &n, &Q) != EOF) {
		clear();
		memset(s, 0, sizeof(s));
		
		bsize = 0;
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			//a[i] = rand();
			b[bsize++] = a[i];
		}
		sortIt();
		for(i = 1; i <= n; ++i) {
			a[i] = getIndex(a[i]);
		}
		
		for(i = 0; i < Q; ++i) {
			I[i].read(i);		
		}
		sort(I, I + Q);
		
		int R = 0;
		for(i = 0; i < Q; ++i) {
			for(j = R + 1; j <= I[i].R; ++j) {
				s[j] = sum( a[j] - 1 );
				add(a[j], n, 1);
			}
			R = I[i].R;
			int idx = I[i].idx;
			int end;
			
			if(i == 0) {
				ans[idx] = 0;
				end = I[i].R;
			}else if(I[i].R == I[i-1].R) {
				ans[idx] = ans[ I[i-1].idx ];
				end = I[i-1].L - 1;
			}else {
				ans[idx] = 0;
				end = I[i].R;
				
			}
			
			for(j = I[i].L; j <= end; ++j) {
				ans[idx] += sum(a[j]-1) - s[j];
			}
		}
		
		for(i = 0; i < Q; ++i) {
			printf("%d\n", ans[i]);
		}
		
	}
	return 0;
}

/*
7 9
31111 2 1 24 433 34 76 
1 2
1 3
2 5
4 7
5 7
6 7
3 7
2 7
1 7
*/
