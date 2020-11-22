#include <iostream>

using namespace std;

#define MAXN 10010

int a[MAXN];
int n;

int solve() {
    int i, start = -1, ans = 0;
    for(i = 1; i <= n; ++i) {
        if(a[i]) {
            start = i;
            break;
        }
    }
    if(start == -1) {
        return 0;
    }
    while(start <= n) {
        int max_n = a[start]<0?1:0, max_p = a[start]>0?1:0;
        if(max_p > ans) ans = max_p;
        for(i = start+1; i <= n && a[i]; ++i) {
            if(a[i] < 0) {
                int x = max_n + 1, y = max_p + 1;
                if(max_n)
                    max_p = x;
                else
                    max_p = 0;
                max_n = y;
            }else {
                max_p ++;
                if(max_n)
                    max_n ++;
                else
                    max_n = 0;
            }
            if(max_p > ans) {
                ans = max_p;
            }
            //printf("%d %d %d\n", i, max_p, max_n);
        }
        for(; i <= n; ++i) {
            if(a[i]) {
                start = i;
                break;
            }
        }
        if(i == n+1) break;
    }
    return ans;
}

int main() {
    int i;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        printf("Case #%d: %d\n", ++cases, solve());
    }
    return 0;
}

/*
10
11
2 -2 2 -2 -2 2 -2 2 -2 2 2 

*/
