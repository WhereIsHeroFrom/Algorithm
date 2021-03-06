/*
题意：给定一棵N(N <= 100000)个结点的树，根为1。删边的操作分为两步：1、删掉某条边；2、删掉边连接的子树；
Alice和Bob轮流删边，最后不能删边的人输。问，Alice先行，最后谁获胜。
题解：克隆法则
      叶子结点sg值为0，长度为i的一条树链的sg值为i。
      某个根上长出的两条分叉（长度分别为i和j）的sg值为i^j。
      那么dfs后续遍历整棵树，可以通过“分支收敛”把树转换成链。最后的异或和==0表示先手败，>0表示先手胜。
*/
#include <iostream>
using namespace std;

#define MAXN 100010

typedef int SG;

int n;
int head[MAXN], tot;

struct Edge {
    int v;
    int next;
    Edge(){}
    Edge(int _v, int _next): v(_v), next(_next) {}
}edge[2*MAXN];

void addEdge(int from, int to) {
    edge[tot] = Edge(to, head[from]);
    head[from] = tot++;
}

SG dfs(int u, int fat) {
    int i;
    SG sg = 0;
    for(i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].v;
        if(v == fat) continue;
        sg ^= (1 + dfs(v, u));
    }
    return sg;
}

void init(int n) {
    int i;
    tot = 0;
    for(i = 1; i <= n; i++) {
        head[i] = -1;    
    }
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        init(n);
        for(i = 0; i < n - 1; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge(x, y);
            addEdge(y, x);
        }
        int sg = dfs(1, 0);
        printf("%s\n", sg?"Alice":"Bob");
    }
    return 0;
}
