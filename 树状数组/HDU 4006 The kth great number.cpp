#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 1000010
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


struct IQ {
    int tp;
    int val;
}I[MAXV];

int a[MAXV], asize;

int binGetAns(int k) {
    int ans;
    int l = 1, r = asize;
    int summax = sum(r) - k;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sum(mid - 1) <= summax) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ans;
}

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

int main() {
    int n, k;
    char cmd[10];
    
    while (scanf("%d %d", &n, &k) != EOF) {
        clear();
		asize = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", cmd);
            if (cmd[0] == 'I') {
            	int x;
            	scanf("%d", &x);
            	I[i].tp = 0;
            	I[i].val = x;
            	a[asize ++] = x;
			}else {
				I[i].tp = 1;
			}
        }
		sortIt();
        
		for(int i = 0; i < n; ++i) {
            if (I[i].tp == 0) {
                add( getIndex( I[i].val ), asize, 1);
            }
            else {
                printf("%d\n", getValue( binGetAns(k) ) );
            }

        }
    }

    return 0;
}

/*
14 5
I 1
I 1
I 1
I 1
I 1
Q
I 2
Q
I 2
I 2
I 3
Q
I 3
Q
*/
