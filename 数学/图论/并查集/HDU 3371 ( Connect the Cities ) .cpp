#include <iostream>
#include <algorithm>

using namespace std;
#define MAXN 1000
#define MAXM 200000

int pre[MAXN], h[MAXN];
int sum[MAXN];
bool flag;
int n, m, k;

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
        pre[fy] = fx;
        sum[fx] += sum[fy];
        if(sum[fx] == n) {
            flag = true;
        }
        return true;
    }
}

class Edge {
public:
    int u, v;
    int val;
    Edge(){} 
    Edge(int _u, int _v, int _val) {
        u = _u;
        v = _v;
        val = _val;
    }
}edges[ MAXM ];

int cmp(const Edge& a, const Edge& b) {
    return a.val < b.val;
} 
    

int s[ MAXN ];

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while( t-- ) {
        flag = false;
        scanf("%d %d %d", &n, &m, &k);
        for(i = 1; i <= n; i++) {
            pre[i] = i;
            sum[i] = 1;
            h[i] = 0;
        }
        for(i = 0; i < m; i++) {
            int u, v, val;
            scanf("%d %d %d", &u, &v, &val);
            edges[i] = Edge(u, v, val);
        }
        sort( edges, edges + m, cmp );
        while(k--) {
            int t;
            scanf("%d", &t);
            for(i = 0; i < t; i++) {
                scanf("%d", &s[i]);
            }
            if( !flag ) {
                for(i = 1; i < t; i++) {
                    unionset_union(s[0], s[i]);
                }
            }
        }
        int ans = 0;
        for(i = 0; i < m; i++) {
            if( unionset_union(edges[i].u, edges[i].v) ) {
                ans += edges[i].val;
            }
            if(flag) break;
        }
        for(i = 1; i <= n; i++) {
            if(sum[i] == n) {
                break;
            }
        }
        if(i > n) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}


/*
10
6 4 3
1 4 2
2 6 1
2 3 5
3 4 33
2 1 2
2 1 3
3 4 5 6

10
5 0 0

*/

