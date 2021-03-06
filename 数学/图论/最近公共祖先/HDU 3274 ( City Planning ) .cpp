#include <iostream>
using namespace std;

#define MAXN 1010

int n, m;
struct edge {
    int to, val;
    int next;
    void reset(int _t, int _v, int _n) {
        to = _t;
        val = _v;
        next = _n;
    }
}E[2*MAXN];

int head[MAXN], tot;
int val[MAXN], fat[MAXN], dep[MAXN];
int mat[MAXN][MAXN], has[MAXN][MAXN];

void addEdge(int from, int to, int val) {
    E[tot].reset(to, val, head[from]);
    head[from] = tot++;
}

void init() {
    int i, j;
    tot = 0;
    for(i = 1; i <= n; ++i) {
        head[i] = -1;
        fat[i] = 0;
        for(j = 1; j <= n; ++j) {
            mat[i][j] = has[i][j] = 0;
        }
    }
}

void build_tree(int d, int u, int f) {
    dep[u] = d;
    fat[u] = f;
    for(int e = head[u]; e != -1; e = E[e].next) {
        int v = E[e].to;
        if(v == f) continue;
        build_tree(d+1, v, u);
    }
}

void mark_edge(int u, int v) {
    has[u][v] = has[v][u] = 1;
}

void lca(int u, int v) {
    if(u == v) {
        return ;
    }
    if(dep[u] < dep[v]) {
        mark_edge(v, fat[v]);
        lca(u, fat[v]);
    }else if(dep[u] > dep[v]){
        mark_edge(u, fat[u]);
        lca(fat[u], v);
    }else {
        mark_edge(v, fat[v]);
        mark_edge(u, fat[u]);
        lca(fat[u], fat[v]);
    }
}

int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        init();
        for(i = 0; i < m; ++i) {
            scanf("%d", &val[i]);
        }
        for(i = 0; i < n - 1; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            addEdge(x, y, z);
            addEdge(y, x, z);
            mat[x][y] = mat[y][x] = z;
        }
        build_tree(0, 1, 0);
        for(i = 0; i < m - 1; ++i) {
            lca(val[i], val[i+1]);
        }
        int ans = 0;
        for(i = 1; i <= n; ++i) {
            for(j = i+1; j <= n; ++j) {
                if(has[i][j]) {
                    ans += mat[i][j];
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
6 3
5 6 1
1 2 3
1 3 1
3 6 4
2 5 4
2 4 2

*/
