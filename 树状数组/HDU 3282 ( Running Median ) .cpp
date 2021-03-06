#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010

int c[MAXN];

int lowbit(int x) {
    return x & (-x);
}

void add(int x) {
    while(x < MAXN) {
        c[x] ++;
        x += lowbit(x);
    }
}

int sum(int x) {
    int s = 0;
    while (x > 0) {
        s += c[x];
        x -= lowbit(x);
    }
    return s;
}

int a[MAXN];
int idx[MAXN], N, tmpN;
int ans[MAXN], anssize;

void init() {
    sort(idx + 1, idx + tmpN + 1);
    N = 1;
    for(int i = 2; i <= tmpN; i++) {
        if(idx[i] != idx[i-1]) {
            idx[++N] = idx[i];
        }
    }
    memset(c, 0, sizeof(c));
}

int getIndex(int v) {
    int l = 1, r = N;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(idx[mid] == v) {
            return mid;
        }
        if(idx[mid] > v) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}

int getKthNumber(int kth) {
    int l = 1, r = N;
    int ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if( sum(mid) >= kth) {
            r = mid - 1;
            ans = mid;
        }else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while(t--) {
        tmpN = 0;
        int c, n;
        scanf("%d %d", &c, &n);
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            idx[ ++tmpN ] = a[i];
        }
        init();
        anssize = 0;
        for(i = 0; i < n; i++) {
             a[i] = getIndex(a[i]);
             add( a[i] );

             if( !(i & 1) ) {
                 ans[ anssize++ ] = idx[ getKthNumber(i/2 + 1) ];
             }
        }
        printf("%d %d\n", c, anssize);
        for(i = 0; i < anssize; i++) {
            printf("%d", ans[i]);
            
            if(i % 10 == 9) printf("\n");
            else if(i != anssize-1)
                printf(" ");
        }
        if(anssize % 10) {
            printf("\n");
        }

    }
    return 0;
}

/*
10
1 9 
1 2 3 4 5 6 7 8 9 
2 9 
9 8 7 6 5 4 3 2 1 
3 23 
23 41 13 22 -3 24 -31 -11 -8 -7 
3 5 103 211 -311 -45 -67 -73 -81 -99 
-33 24 56
4 19 
23 41 13 22 -3 24 -31 -11 -8 -7 
3 5 103 211 -311 -45 -67 -73 11
*/

