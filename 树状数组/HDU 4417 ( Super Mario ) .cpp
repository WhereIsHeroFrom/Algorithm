#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010

int c[MAXN];

int lowbit(int x) { return x & -x; }

void add(int x, int v) { 
    while(x < MAXN) { 
        c[x] += v;
        x += lowbit(x); 
    }
}

int sum(int x) {
    int s = 0;
    while(x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}

int a[MAXN];
int b[MAXN], bs, L;

struct Interval {
    int l, r, H;
    int idx;
    void read(int _i) {
        idx = _i;
        scanf("%d %d %d", &l, &r, &H);
        l ++;
        r ++;
    }
}I[MAXN];

int cmp(Interval a, Interval b) {
    if(a.H == b.H) {
        return a.idx < b.idx;
    }
    return a.H < b.H;
}

int ans[MAXN];

int main() {
    int n, m;
    int i;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        L = 1;
        bs = 0;
        for(i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            I[i].l = I[i].r = i + 1;
            I[i].H = x;
            I[i].idx = -1;
        }
        for(i = 0; i < m; i++) {
            I[n+i].read(i);
        }
        
        sort(I, I + n + m, cmp);
        for(i = 1; i < MAXN; i++) {
            c[i] = 0;
        }
        for(i = 0; i < n+m; i++) {
            if(I[i].idx == -1) {
                add(I[i].l, 1);
            }else {
                ans[ I[i].idx ] = sum(I[i].r) - sum(I[i].l - 1);
            }
        }
        
        printf("Case %d:\n", ++cases);
        for(i = 0; i < m; i++) {
            printf("%d\n", ans[i]);
        }
        
    }
    return 0;
}
