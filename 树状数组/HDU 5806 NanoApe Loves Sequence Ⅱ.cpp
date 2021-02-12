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

int val[MAXV];

// 这个是最快的
char line[MAXV * 12];

void get() {
    int idx = 0, t = 0, s = 0;
    getchar();
    gets(line);

    while (line[idx]) {
        if (line[idx] >= '0' && line[idx] <= '9') {
            s = s * 10 + line[idx] - '0';
        }
        else {
        	if(s) { 
            	val[t++] = s;
            	s = 0;
            } 
        }
        ++idx;
    }
    if (s) {
        val[t++] = s;
    }
}


int main() {
    int n, m, k;
    int t;
    scanf("%d", &t);
    while (t--) {
    	
		scanf("%d %d %d", &n, &m, &k);
        clear();
		asize = 0;
        get();
        for(int i = 0; i < n; ++i) {
        	a[asize ++] = val[i];
        }

		sortIt();
        int l = 0;
        ll ans = 0;
		for(int i = 0; i < n; ++i) {
			val[i] = getIndex(val[i]);
		}
		for(int i = 0; i < n; ++i) {
			add(val[i], asize, 1);
			
			while(i - l + 1 >= k) {	
				int kIndex = binGetAns(k);
				int kVal = getValue(kIndex);
				if(kVal >= m) {
					ans += n - i;	
					add(val[l], asize, -1);
					++l;
				}else {
					break;
				}
			}
        }
        printf("%lld\n", ans);
    }

    return 0;
}

