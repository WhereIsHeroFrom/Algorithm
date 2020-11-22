#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 8
#define MAXS (1<<MAXN)
#define ll __int64

const int T = MAXN*MAXN;

char mat[MAXN+1][MAXN+1];
int hashv[MAXN][MAXN];
int n, ans;

int pos[8][2] = {
    {-2, -1}, 
    {-2, 1},     
    {-1, 2}, 
    {-1, -2},
    {1, -2}, 
    {1, 2}, 
    {2, -1}, 
    {2, 1}, 
};

// dp[i][j][s1][s2] 
// 到第i行为止总共放置j个骑士后，第i-1行状态s1，第i行状态s2 的方案数 
int dp[MAXN+1][11][MAXS][MAXS];

int mask[MAXS][2];
int cntOne[MAXS], codes[MAXN+1];
vector <int> stateOp[MAXS][MAXS]; 

int packState(int cnt, int preLineMask, int nowLineMask) {
    return cnt << 16 | preLineMask << 8 | nowLineMask;
}

void preCalcState() {
    int i, j, k;
    
    for(i = 0; i < MAXS; ++i) {
        mask[i][0] = 0;
        mask[i][1] = 0;
        for(j = 0; j < MAXN; ++j) {
            int needPut = (i & (1<<j));
            if(needPut) {
                // 对一行的影响 
                if(j-2 >= 0) {
                    mask[i][0] |= (1<<(j-2));
                } 
                if(j+2 < MAXN) {
                    mask[i][0] |= (1<<(j+2));
                }
                
                // 对两行的影响
                if(j-1 >= 0) {
                    mask[i][1] |= (1<<(j-1));
                } 
                if(j+1 < MAXN) {
                    mask[i][1] |= (1<<(j+1));
                }
            }
        }
    }
    
    for(i = 0; i < MAXS; ++i) {
        for(j = 0; j < MAXS; ++j) {
            if( mask[i][0] & j ) continue;
            if( mask[j][0] & i ) continue;
            if( cntOne[i] + cntOne[j] > 10) {
                continue;
            }
            for(k = 0; k < MAXS; ++k) {
                if( mask[k][0] & j ) continue;
                if( mask[j][0] & k ) continue;
                
                if( mask[i][1] & k ) continue;
                if( mask[k][1] & i ) continue;
                
                stateOp[i][j].push_back(k);
            }
        }
    }
} 

void preCntOne() {
    for(int i = 0; i < MAXS; ++i) {
        int u = i;
        cntOne[i] = 0;
        while(u) {
            cntOne[i] += (u&1);
            u >>= 1;
        }
    }
}

ll solve(int n) {
    int i, j, k;
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;
    for(i = 1; i <= MAXN; ++i) {
        for(j = 0; j <= n; ++j) {
            for(int s = 0; s < MAXS; ++s) {
                for(int t = 0; t < MAXS; ++t) {
                    if(dp[i-1][j][s][t]) {
                        for(k = stateOp[s][t].size()-1; k >= 0; --k) {
                            int state = stateOp[s][t][k];
                            if( j + cntOne[state] > n) {
                                continue;
                            }
                            if(state & codes[i]) {
                                continue;
                            }
                            dp[i][j + cntOne[state]][t][state] += dp[i-1][j][s][t];
                        }
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(i = 0; i < MAXS; ++i) {
        for(j = 0; j < MAXS; ++j) {
            ans += dp[MAXN][n][i][j];
            
        }
    }
    return ans;
}
int main() {
    int t;
    int i, j;
    preCntOne();
    preCalcState();

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= MAXN; i++) {
            codes[i] = 0;
            scanf("%s", mat[i]);
            for(j = MAXN-1; j >= 0; --j) {
                codes[i] = codes[i] << 1 | (mat[i][j] == '*' ? 1 : 0);
            }
        }
        printf("%I64d\n", solve(n));
        
    }
    return 0;
} 
