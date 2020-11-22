#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 101
#define MAXM 100010

struct Item {
    int val;
    int price;
    void read() {
        scanf("%d %d", &val, &price);
    }
}I[MAXN];

int n, m;
int dp[MAXM];

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int i, j;
    while(scanf("%d", &n) != EOF) {
        for(i = 0; i < n; ++i) {
            I[i].read();
        }
        scanf("%d", &m);
        int p = 0;
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for(i = 0; i < n; ++i) {
            for(j = I[i].price; j <= m; ++j) {
                dp[j] = Max(dp[j], dp[j - I[i].price] + I[i].val);
            }
        }
        int ans = 0;
        for(j = 0; j <= m; j++) {
            if(dp[j] > ans) ans = dp[j];
        }
        printf("%d\n", ans);
    }
    return 0;
}
