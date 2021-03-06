#include <iostream>

using namespace std;

#define MAXN 1000010

int n;
int Max, len;
int a[MAXN], sum[MAXN], L[MAXN], R[MAXN];

void getL() {
    int i;
    for(i = 1; i <= n; ++i) {
        L[i] = i;
        if(i > 1) {
            if(a[i] >= 0) {
                if(a[i-1] >= 0) {
                    L[i] = L[i-1];
                }else {
                    L[i] = i;
                }
            }
        }
    }
}

void getR() {
    int i;
    for(i = n; i >= 1; --i) {
        R[i] = i;
        if(i < n) {
            if(a[i] >= 0) {
                if(a[i+1] >= 0) {
                    R[i] = R[i+1];
                }else {
                    R[i] = i;
                }
            }
        }
    }
}

int main() {
    int i;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }
        getL();
        getR();
        
        int zero = 0, maxNeg = -1000000001;
        len = 0, Max = 0;        
        
        for(i = 1; i <= n; i = R[i] + 1) {
            int v = sum[R[i]] - sum[L[i]-1];
            //printf("%d %d %d %d\n", i, L[i], R[i], v);
            
            if(v > 0) {
                Max += v;
                ++len;
            }else if(v == 0) {
                zero = 1;
            }else if(v < 0) {
                if(v > maxNeg) {
                    maxNeg = v;
                }
            }
        }
        if(Max == 0) {
            len = 0;
        }
        printf("Case %d:\n", ++cases);
        printf("%d %d\n", len, Max);
        if(t) {
            puts("");
        }
    }
    return 0;
} 

/*
20
14
1 -1 2 2 3 4 5 -4 0 0 -3 2 0 2
*/

