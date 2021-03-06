#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 200010

class Edge {
public:
    int u, v, val;
    int next;
    Edge() {}
    Edge(int _u, int _v, int _val, int _n) {
        u = _u;
        v = _v;
        val = _val;
        next = _n;
    }
}edges[ MAXN ];
int head[ MAXN ], tot;

int cmp(const Edge x, const Edge y) {
    return x.val > y.val;
}

int pre[MAXN], h[MAXN];
int cir_cnt[MAXN];

int unionset_find(int p) {
    int x = p;
    while(pre[p] != p) {
        p = pre[p];
    }
    /*while(x != p) {
        int tmp = pre[x];
        pre[x] = p;
        x = tmp;
    }*/
    return p;
}

int unionset_union(int x, int y) {
    int fx = unionset_find(x);
    int fy = unionset_find(y);
    if(fx == fy) {
        return false;
    }else {
        if( h[fx] == h[fy] ) {
            pre[fy] = fx;
            h[fx]++;
            
            cir_cnt[fx] += cir_cnt[fy];
        }else if( h[fx] < h[fy] ) {
            pre[fx] = fy;
            
            cir_cnt[fy] += cir_cnt[fx];
        }else {
            pre[fy] = fx;
            
            cir_cnt[fx] += cir_cnt[fy];
        }
        return true;
    }
}

void addEdge (int u, int v, int val) {
    edges[ tot ] = Edge(u, v, val, head[u]);
    head[u] = tot++;
}

int n, m;

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF && (n+m) ) {
        tot = 0;
        for(i = 0; i < n; i++) {
            head[i] = -1;
            h[i] = 0;
            pre[i] = i;     
            cir_cnt[i] = 0;       
        }
        
        for(i = 0; i < m; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            addEdge(x, y, z);
        }
        
        
        sort(edges, edges + m, cmp);
        
        int max = 0;
        
        for(i = 0; i < m; i++) { 
            int fu = unionset_find(edges[i].u);
            int fv = unionset_find(edges[i].v);
            if ( fu == fv ) {
                // 如果已经在同一个连通块，那么判断该块中的环的数量，
                // 没有环的情况下可以连接这条边
                if ( !cir_cnt[fu] ) {
                    cir_cnt[fu] ++;
                    max += edges[i].val;
                } 
            }else {
                // 如果不在同一个连通块，那么两个连通块的环总数量和小于等于1的情况才能连接 
                if( cir_cnt[fu] + cir_cnt[fv] <= 1) {
                    unionset_union(fu, fv);
                    max += edges[i].val;
                }
            }
        }
        printf("%d\n", max);
    }
    return 0;
}

/*
10 10
0 1 1
1 2 1
2 0 1
3 4 1
4 5 1
5 3 1
6 7 2
7 8 2
8 6 2
6 9 120
*/

