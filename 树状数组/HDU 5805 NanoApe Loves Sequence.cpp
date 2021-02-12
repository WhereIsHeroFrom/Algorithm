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

int ABS(int x) {
	return x < 0 ? -x : x;
}

void process(int idxsize, int *idx, int val) {
	for(int i = 0; i < idxsize; ++i) {
		add(idx[i], asize, val);
	}	
} 

int main() {
    int n, m, k;
    int t;
    int i;
    scanf("%d", &t);
    while (t--) {
		scanf("%d", &n);
        clear();
		asize = 0;
        get();
        for(i = 1; i < n; ++i) {
        	a[asize ++] = ABS(val[i] - val[i-1]);
        }
        for(i = 1; i < n - 1; ++i) {
        	a[asize++] = ABS(val[i-1] - val[i+1]); 
		}
		sortIt();
		
		for(i = 1; i < n; ++i) {
			int idx = getIndex( ABS(val[i] - val[i-1]) );
			add(idx, asize, 1);
		}
		
		ll ans = 0;
		
		int idx[2][5];
		int idxsize[2];
		
		// 0 表示要增加的， 1 表示要去掉的 
		for(i = 0; i < n; ++i) {
			idxsize[0] = idxsize[1] = 0;
			
			// 删掉第 i 个
			if(i == 0) {
				idx[1][ idxsize[1]++ ] = getIndex( ABS(val[1] - val[0]) );
			}else if(i < n - 1) {
				
				idx[0][ idxsize[0]++ ] = getIndex( ABS(val[i-1] - val[i+1]) );
				
				idx[1][ idxsize[1]++ ] = getIndex( ABS(val[i] - val[i-1]) );
				idx[1][ idxsize[1]++ ] = getIndex( ABS(val[i] - val[i+1]) );
				
			}else {
				idx[1][ idxsize[1]++ ] = getIndex( ABS(val[i] - val[i-1]) );
			}

			
			process(idxsize[0], idx[0], 1);
			process(idxsize[1], idx[1], -1);
			
			int kIndex = binGetAns(1);
			int kVal = getValue(kIndex);
			ans += kVal; 

			process(idxsize[0], idx[0], -1);
			process(idxsize[1], idx[1], 1);
			
			
		}
		
        printf("%lld\n", ans);
    }

    return 0;
}

