/*
题意：
    给定一个图，求这个图是否是个二分图，如果是求它的最大匹配。
题解：
    判断一个图是否为二分图，可以采用染色，每次找到一个尚未染色的点
将它染成白色，然后所有相邻点必然要染成黑色，在染色过程中如果遇到已
经染色的点，那么判断这个染色是否和之前的染色冲突，如果冲突说明必定
存在奇圈，不是二分图。
*/
#include <iostream>

using namespace std;

#define MAXN 420
#define MAXM 100000

#define COLOR_UNDEF -1

class Edge {
public:
    int u, v, next;
    Edge() {

    }
    Edge( int _u, int _v, int _n ) {
        u = _u;
        v = _v;
        next = _n;
    }
}edges[MAXM];
int head[MAXN], tot;
int n;
void addEdge(int x, int y) {
    edges[tot] = Edge(x, y, head[x]);
    head[x] = tot++;
}

int color[MAXN];


bool color_it(int pt, int c) {
    if(color[pt] != COLOR_UNDEF) {
        return color[pt] == c;
    }
    color[pt] = c;
    for(int i = head[pt]; i != -1; i = edges[i].next) {
        if( !color_it( edges[i].v, 1-c ) ) {
            return false;
        }
    }
    return true;
}

bool visited[MAXN];
int pre[MAXN];

bool dfs(int u) {
    for(int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if( visited[v] ) {
            continue;
        }
        visited[v] = 1;
        int k = pre[v];
        pre[v] = u;
        if(k == -1 || dfs(k) ) {
            return true;
        }
        pre[v] = k;
    }
    return false;
}

int main() {
    int m;
    int i;
    while( scanf("%d %d", &n, &m) != EOF ) {
        tot = 0;
        memset(head, -1, sizeof(head));
        memset(color, COLOR_UNDEF, sizeof(color));

        while(m--) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge(x, y);
            addEdge(y, x);
        }

        for(i = 1; i <= n; i++) {
            if( color[i] == COLOR_UNDEF ) {
                if( !color_it(i, 0) ) {
                    break;
                }
            }
        }

        if(i <= n) {
            printf("No\n");
        }else {
            int M = 0;
            memset(pre, -1, sizeof(pre));
            for(i = 1; i <= n; i++) {
                memset(visited, 0, sizeof(visited));
                if( dfs(i) ) M ++;
            }
            printf("%d\n", M/2);
        }
    }
    return 0;
} 

