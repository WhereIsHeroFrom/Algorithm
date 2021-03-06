#include <iostream>

using namespace std;

int n;
#define MAXN 16
#define inf -100000000.0
double totalArea;

struct Couple {
    double Price;
    double PriceOfLog;
    double Area;
    void read() {
        int a, p;
        scanf("%d %d", &p, &a);
        Area = a;
        totalArea += a;

        Price = p;
        PriceOfLog = log(1.0*p);
    }
}C[MAXN];

double mat[MAXN][MAXN];
double dp[1<<MAXN];

bool invalid(double v) {
    return v < inf;
}

double dfs(int state) {
    int i, j;
    if( !invalid(dp[state]) ) {
        return dp[state];
    }

    double minPrice = inf - 1;
    for(i = 0; i < n; i++) {
        if(state & (1<<i)) {
            int nextstate = state ^ (1<<i);
            double priceOfLog = C[i].PriceOfLog;
            for(j = 0; j < n; ++j) {
                if(nextstate & (1<<j)) {
                    if( !invalid(mat[j][i]) ) {
                        priceOfLog += mat[j][i];
                    }
                }
            }
            double price = exp(priceOfLog) + dfs(nextstate);
            if(invalid(minPrice) || price < minPrice) {
                minPrice = price;
            }
        }
    }
    return dp[state] = minPrice;
}

int main() {
    int i, j, k;

    while(scanf("%d", &n) != EOF && n) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                mat[i][j] = inf - 1;    
            }
        }
        totalArea = 0;
        for(i = 0; i < n; ++i) {
            C[i].read();
            scanf("%d", &k);
            while(k--) {
                int id, v;
                scanf("%d %d", &id, &v);
                --id;
                mat[i][id] = log((100-v)/100.0);
            }
        }
        for(i = 0; i < (1<<n); ++i) {
            dp[i] = i?(inf - 1):0;
        }
        dp[(1<<n)-1] = dfs((1<<n)-1);
        double minAns = inf - 1;
        for(i = 1; i < (1<<n); ++i) {
            double A = 0;
            for(j = 0; j < n; j++) {
                if(i & (1<<j)) {
                    A += C[j].Area;
                }
            }
            //printf("%d %lf %lf\n", i, dp[i], A);
            double val = dp[i] / A;
            if(val < minAns || invalid(minAns)) {
                minAns = val;
            }
        }
        printf("%.4lf\n", minAns);
    }
    return 0;
}
