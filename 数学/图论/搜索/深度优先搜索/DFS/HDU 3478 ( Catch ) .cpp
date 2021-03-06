#include <iostream>
#include <cstring>

using namespace std;

#define LL __int64
#define MAXN 100010
#define MAXM 1000010 

struct Edge {
    int v;
    int next;
    Edge(){}
    Edge(int _v, int _next): v(_v), next(_next) {
    }
}E[MAXM];

int head[MAXN], tot;
int n, m;

void addEdge(int x, int y) {
    E[tot] = Edge(y, head[x]);
    head[x] = tot++;
}

int color[MAXN];
int oddLoop;

void dfs(int u) {
    for(int e = head[u]; e != -1; e = E[e].next) {
        int v = E[e].v;
        if(color[v] == -1) {
            color[v] = 1 - color[u];
            dfs(v);
        }else if(color[v] == color[u]) {
            oddLoop = true;
        }
    }
}

bool solve(int s) {
    color[s] = 0;
    oddLoop = false;
    dfs(s);
    
    int i;
    for(i = 0; i < n; ++i) {
        if(color[i] == -1) {
            return false;
        }
    }
    return oddLoop;
}

int main() {
    int t, cases = 0;
    int i, s;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &s);
        memset(head, -1, sizeof(head));
        memset(color, -1, sizeof(color));
        tot = 0;
        for(i = 0; i < m; ++i) {
            int x, y, z;
            scanf("%d %d", &x, &y);
            addEdge(x, y);
            addEdge(y, x);
        }
        printf("Case %d: %s\n", ++cases, solve(s) ? "YES": "NO");
    }
    return 0;
}
