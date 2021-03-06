#include <iostream>
#include <cstring>

using namespace std;

#define LL __int64
#define MAXN 10010
int n;

struct Edge {
    int v;
    LL val;
    int next;
    Edge(){}
    Edge(int _v, LL _val, int _next): v(_v), val(_val), next(_next) {
    }
}E[MAXN*2];

int head[MAXN], tot;
int sum[MAXN];
LL ans;

void addEdge(int x, int y, LL z) {
    E[tot] = Edge(y, z, head[x]);
    head[x] = tot++;
}

int dfs(int u, int fat) {
    int i;
    int cnt = 1;
    for(i = head[u]; ~i; i = E[i].next) {
        Edge &e = E[i];
        if( e.v == fat ) {
            continue;
        }
        int soncnt = dfs(e.v, u);
        ans += e.val * (LL)soncnt * (LL)(n - soncnt);
        cnt += soncnt;
    }
    return cnt;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        tot = 0;
        for(i = 0; i < n-1; ++i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            addEdge(x, y, z);
            addEdge(y, x, z);
        }
        ans = 0;
        dfs(0, -1);
        int f = n* (n-1)/2;
        printf("%.6lf\n", ans * 1.0 / f);
    }
    return 0;
}
