#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef double ValueType;
const int maxn = 110;
const int maxm = 2000010;
const ValueType inf = -1e9;

struct Edge {
    int u, v, next;
    ValueType w;
    Edge(){}
    Edge(int _u, int _v, ValueType _w, int _next) :
        u(_u), v(_v), w(_w), next(_next)
    {
    }
}edges[maxm];

int head[maxn], edgeCount;
ValueType dist[maxn];
bool visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

bool BellmanFordUpdate() {
    bool flag = false;
    for (int i = 0; i < edgeCount; ++i) {
        Edge &edge = edges[i];

        if (dist[edge.u] * edge.w > dist[edge.v]) {
            flag = true;
            dist[edge.v] = dist[edge.u] * edge.w;
        }
    }
    return flag;
}

bool mat[maxn][maxn];

bool BellmanFord(int n) {
    for (int i = 0; i < n; ++i) {
        dist[i] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (!BellmanFordUpdate()) {
            return false;
        }
    }
    return BellmanFordUpdate();
}


void floyed(int n) {
    int i, j, k;
    for (k = 0; k < n; ++k) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                mat[i][j] = mat[i][j] || (mat[i][k] && mat[k][j]);
            }
        }
    }
}

char name[maxn][110];
char from[110], to[110];

int findname(int n, char *namestr) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(namestr, name[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n, m, l;
    int i, j, k;
    int cas = 0;
    while (scanf("%d", &n) != EOF && n) {
        init();
        for (i = 0; i < n; ++i) {
            scanf("%s", name[i]);
        }
        scanf("%d", &m);
        while (m--) {
            double val;
            scanf("%s %lf %s", from, &val, to);
            int f = findname(n, from);
            int t = findname(n, to);
            addEdge(f, t, val);
        }
        if (BellmanFord(n)) {
            printf("Case %d: Yes\n", ++cas);
        }
        else {
            printf("Case %d: No\n", ++cas);
        }

    }
    return 0;
}