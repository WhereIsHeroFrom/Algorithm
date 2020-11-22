#include <iostream>
#include <algorithm>
#include <cstring> 
using namespace std;

#define MAXN 1010

struct Intval {
    int s, e, c;
    bool operator < (Intval other) {
        return e < other.e;
    }
    void read() {
        scanf("%d %d %d", &s, &e, &c);
    }
}I[MAXN];

int m, n;
int dp[MAXN];

int MMax(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &m, &n);
        for(i = 1; i <= n; ++i) {
            I[i].read();
        }
        sort(I+1, I+n+1);
        memset(dp, -1, sizeof(dp));
        I[0].s = I[0].e = I[0].c = 0;
        dp[0] = 0;
        int Max = 0;
        for(i = 1; i <= n; ++i) {
            if(I[i].e > m) break;
            
            for(j = 0; j < i; ++j) {
                if(I[j].e < I[i].s) {
                    if(dp[j] != -1 && I[i].c + dp[j] > dp[i]) {
                        dp[i] = I[i].c + dp[j];
                    }
                }else {
                    break;
                }
            }
            if(dp[i] > Max) Max = dp[i];
        }
        printf("%d\n", Max);
    }
    return 0;
}
/*
10
15 5
1 5 100
3 10 10
5 10 100
1 4 2
14 15 266

5 5
1 1 1
2 2 1
3 3 1
4 4 1
5 5 1

*/
