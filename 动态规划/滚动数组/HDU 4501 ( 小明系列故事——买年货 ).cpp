#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 102
#define MAXK 6

int dp[2][MAXK][MAXN][MAXN];

struct Item {
    int a, b;
    int val;
    void read() {
        scanf("%d %d %d",&a, &b, &val);
    }
}I[MAXN]; 

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, v1, v2, k;
    int i;
    while( scanf("%d %d %d %d", &n, &v1, &v2, &k) != EOF ) {
        for(i = 0; i < n; ++i) {
            I[i].read();
        }
        memset(dp, -1, sizeof(dp));
        int totalMax = 0;
        dp[0][0][0][0] = 0;
        int p = 0;
        for(i = 0; i < n; ++i) {
            for(int fre = 0; fre <= k; ++fre) {
                for(int price = 0; price <= v1; ++price) {
                    for(int score = 0; score <= v2; ++score) {
                        dp[p^1][fre][price][score] = -1;
                    }
                }                
            }
            
            for(int fre = 0; fre <= k; ++fre) {
                for(int price = 0; price <= v1; ++price) {
                    for(int score = 0; score <= v2; ++score) {
                        int &dpv = dp[p^1][fre][price][score];
                        // 第i个商品不买
                        dpv = dp[p][fre][price][score];
                        // 第i个商品免费拿
                        if(fre >= 1 && dp[p][fre-1][price][score] != -1) {
                            dpv = Max(dpv, dp[p][fre-1][price][score] + I[i].val);
                        }
                        // 第i个商品用钱买
                        if(price >= I[i].a && dp[p][fre][price - I[i].a][score] != -1) {
                            dpv = Max(dpv, dp[p][fre][price - I[i].a][score] + I[i].val);
                        } 
                        // 第i个商品用积分换
                        if(score >= I[i].b && dp[p][fre][price][score - I[i].b] != -1) {
                            dpv = Max(dpv, dp[p][fre][price][score - I[i].b] + I[i].val);
                        } 
                        if(dpv > totalMax) {
                            totalMax = dpv;
                        }
                    }
                }                
            }
            p ^= 1;
        }    
        printf("%d\n", totalMax); 
    } 
    return 0;
}
