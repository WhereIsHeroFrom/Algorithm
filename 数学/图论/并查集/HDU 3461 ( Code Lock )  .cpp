/*
题意： 
    给定一些区间，求不同区间的种类数，不同的意思为任何两个区间没有包含关系。

题解：     
    并查集
    对于区间[a, b]，查询a-1和b在集合中的关系，如果在同一集合，说明之前已经出现过
一些集合能够组合出[a, b]，否则计数器加1。
    由于内存限制，并查集优化可以采用路径压缩。 
*/
#include <iostream>

using namespace std;

#define LL __int64
#define MOD 1000000007
#define MAXN 10000010

int pre[MAXN];

LL EXP(LL a, LL b, LL c) {
    if(b == 0) {
        return 1;
    }
    return EXP( (a*a)%c, b/2, c ) * (b&1?a:1) % c;  
}

int unionset_find(int p) {
    int x = p;
    while(pre[p] != p) {
        p = pre[p];
    }
    while(x != p) {
        int tmp = pre[x];
        pre[x] = p;
        x = tmp;
    }
    return p;
}

int unionset_union(int x, int y) {
    int fx = unionset_find(x);
    int fy = unionset_find(y);
    if(fx == fy) {
        return false;
    }else {
        
        /*if( h[fx] == h[fy] ) {
            pre[fy] = fx;
            h[fx]++;
        }else if( h[fx] < h[fy] ) {
            pre[fx] = fy;
        }else {
            pre[fy] = fx;
        }*/
        pre[fx] = fy;
        return true;
    }
}
int n, m;

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF) {
        for(i = 0; i <= n; i++) pre[i] = i;
        int cnt = 0;
        for(i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            if( unionset_union(y, x-1) ) {
                cnt++;
            }
        }
        printf("%I64d\n", EXP(26, n-cnt, MOD) );
    }
    return 0;
}

