#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define LL __int64

LL P[3];
int n;
int ansCnt;
LL ans[100000];

void dfs(int depth, int maxDepth, LL v, double lgv) {
    int i;
    if(lgv > 18*log(10.0)) {
        return ;
    }
    if(depth == maxDepth) {
        if(v == 1) return ;
        ans[ ansCnt++ ] = v;
        //printf("%I64d\n", v);
        return ;
    }

    LL p = 1;
    double lgp = log(P[depth]*1.0);
    double totlgp = 0;
    for(i = 0; ; ++i) {
        dfs(depth+1, maxDepth, v*p, lgv + totlgp);
        if(lgv + totlgp > 18*log(10.0)) return ;
        p*= P[depth];
        totlgp += lgp;
    }
}

int main() {
    while( scanf("%I64d %I64d %I64d %d", &P[0], &P[1], &P[2], &n) != EOF ) {
        ansCnt = 0;
        dfs(0, 3, 1, 0);
        sort(ans, ans + ansCnt);
        printf("%I64d\n", ans[n-1]);
    }
    return 0;
}
