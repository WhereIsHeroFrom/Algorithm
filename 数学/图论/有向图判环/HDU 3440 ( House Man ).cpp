#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 1010
#define INF 12345678

struct edge {
    int from, to, val, next;
    edge() {
    }
    edge(int _f, int _t, int _v, int _n) {
        from = _f;
        to = _t;
        val = _v;
        next = _n;
    }
}E[MAXN*4];

int n;
int dis[MAXN];
int visitCount[MAXN];
int head[MAXN], tot;

// 返回是否存在环 
// 解决 d[x] - d[y] <= C 的问题
// 最短路模板 其中C = w(y, x) 
bool spfa(int s) {
    int i;
    for(i = 1; i <= n; i++) {
        dis[i] = INF;
        visitCount[i] = 0;
    }
    dis[s] = 0;
    
    queue <edge> Q;
    Q.push( edge(-1, s, 0, -1) );
    
    while( !Q.empty() ) {
        edge now = Q.front();
        Q.pop();
        
        int from = now.to;
        int predist = now.val;
        
        if( visitCount[from]++ > n ) {
            return true;
        }
        
        for(i = head[from]; i != -1; i = E[i].next) {
            int to = E[i].to;
            int nextdist = E[i].val + predist;
            
            if(nextdist < dis[to] || dis[to] == INF) {
                dis[to] = nextdist;
                Q.push( edge(from, to, nextdist, -1) );
            }
        }    
    }
    
    return false;
}

void addEdge(int u, int v, int c) {
    E[tot] = edge(u, v, c, head[u]);
    head[u] = tot++;
}


struct House {
    int idx, height;
}H[MAXN]; 

int cmp(House a, House b) {
    return a.height < b.height;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int t, cases = 0;
    int D;
    int i;
    scanf("%d", &t);
    while( t-- ) {
        memset(head, -1, sizeof(head));
        tot = 0;

        scanf("%d %d", &n, &D);
        for(i = 1; i <= n; i++) {
            scanf("%d", &H[i].height);
            H[i].idx = i;
        }
        sort(&H[1], &H[1] + n, cmp);
        
        for(i = 1; i < n; i++) {
            //printf("%d %d\n", H[i].idx, H[i+1].idx);
            int v = Max( H[i].idx, H[i+1].idx );
            int u = Min( H[i].idx, H[i+1].idx );
            addEdge(u, v, D);
        }
        for(i = 2; i <= n; i++) {
            addEdge(i, i-1, -1);
        }
        
        int start = Min( H[1].idx, H[n].idx );
        int end = Max( H[1].idx, H[n].idx );
        bool ans = spfa(start);
        printf("Case %d: ", ++cases);
        if( ans ) {
            printf("-1\n");
        }else {
            if(dis[end] == INF) dis[end] = -1;
            printf("%d\n", dis[end]);
        }
    }
    return 0;
}

