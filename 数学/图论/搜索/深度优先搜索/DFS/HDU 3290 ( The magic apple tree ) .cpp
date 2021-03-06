#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 20010
struct Edge {
    int v, next;
    Edge() {
        
    }
    Edge(int _v, int _next) {
        v = _v;
        next = _next;
    }
}E[MAXN];
int head[MAXN];
int tot;


int deg[MAXN];
int a[MAXN];
int value[MAXN];

void addEdge(int u, int v) {
    E[tot] = Edge(v, head[u]);
    head[u] = tot++; 
}

int dfs(int u) {
    if(head[u] == -1) {
        return u;
    }
    int e;
    for(e = head[u]; e != -1; e = E[e].next) {
        int v = E[e].v;
        value[v] = dfs(v);
    }
    
    int size = 0;
    for(e = head[u]; e != -1; e = E[e].next) {
        a[size++] = value[ E[e].v ];
    }
    sort(a, a + size);
    return a[ (size + 1)/2-1 ];
}

char str[1000000];
int x[MAXN];

void scan(char *str) {
    int idx = 0;
    int now = 0, s = -1;
    while(1) {
        if(str[idx] >= '0' && str[idx] <= '9') {
            if(s == -1) s = 0;
            s = s * 10 + (str[idx] - '0');
        }else {
            if(s != -1) {
                x[now++] = s;
                s = -1;
            }
        }
        
        if( !str[idx] ) break;
        ++idx;
    }
}
int main() {
    int n, i, j;
    while(scanf("%d", &n) != EOF) {
        memset(deg, 0, sizeof(deg));
        memset(head, -1, sizeof(head));
        tot = 0;
        getchar();
        
        for(i = 1; i <= n; ++i) {
            int k;
            gets(str);
            scan(str);
            
            for(j = 1; j <= x[0]; ++j) {
                addEdge(i, x[j]);
                deg[ x[j] ] = 1;
            }
        }
        for(i = 1; i <= n; ++i) {
            if(!deg[i]) {
                printf("%d\n", dfs(i));
                break;
            }
        }
    }
    return 0;
} 
