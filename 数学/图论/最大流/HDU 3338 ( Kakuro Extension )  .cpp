#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define INF 10000000 
 
const int MAXN = 21000;   // 最大点数 
const int MAXM = 1000000; // 最大边数 


class Edge {
    public:
    int from, to;
    int next;
    int cap;
    Edge() {}
    Edge(int _f, int _t, int _c, int _nxt) {
        from = _f;
        to = _t;
        cap = _c;
        next = _nxt;
    }
}E[ MAXM ];

int head[MAXN], newhead[MAXN];
int total; 
int n;
int dist[MAXN];    // dist[i]表示终点到i点的最短路 
int dcnt[MAXN];    // dcnt[x] = cnt 表示当前网络中 dist[v] == x 的有cnt个 

void init() {
    total = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int c) {
    // 正向边 
    E[ total ] = Edge(u, v, c, head[u]);
    head[u] = total++;
    // 反向边 
    E[ total ] = Edge(v, u, 0, head[v]);
    head[v] = total++;
}

// 预处理dist数组
// dist[v]表示从v到end的最短路（有一条边则长度为1） 
void sap_bfs(int start, int end) {
    memset(dist, -1, sizeof(dist));
    memset(dcnt, 0, sizeof(dcnt));
    // 汇点的dist数组 
    dist[end] = 0;
    dcnt[ dist[end] ] = 1;
    
    queue < int > Q;
    Q.push( end );
    
    while( !Q.empty() ) {
        int u = Q.front();
        Q.pop();
        
        for(int e = head[u]; e != -1; e = E[e].next) {
            int v = E[e].to;
            if ( dist[v] == -1) {
                dist[v] = dist[u] + 1;
                dcnt[ dist[v] ] ++;
                Q.push(v);
            }
        }
    }
}

int stack[ MAXN ], top;

int sap(int start, int end) {
    int i, e;
    int maxflow = 0; 
    
    sap_bfs(start, end);
    top = 0;
    for(i = 0; i < MAXN; i++) {
        newhead[i] = head[i];
    }
    
    int u = start;
    while ( dist[start] < n ) {
        
        if(u == end) {
            int flow = INF;
            int criticalE = -1;
            // 找到当前路径的可行流 
            for(i = 0; i < top; i++) {
                int e = stack[i];    // 边编号 
                if( E[e].cap < flow) {
                    flow = E[e].cap;
                    criticalE = i;
                }
            }
            // 类似EK算法， 更新残留网络 
            for(i = 0; i < top; i++) {
                int e = stack[i];
                E[e].cap -= flow;
                E[e^1].cap += flow;
            }
            maxflow += flow;
            top = criticalE;
            u = E[ stack[top] ].from;
        }else {
            // 从u这个点无法找到一条可行弧 (u, v)
            // 满足 dist[u] = dist[v] + 1
            // 表明无增广路 
            if( dcnt[ dist[u] - 1 ] == 0 ) {
                break;
            }
        }
        
        for(e = newhead[u]; e != -1; e = E[e].next) {
            if( E[e].cap ) {
                if( dist[u] == dist[ E[e].to ] + 1 ) {
                    break;
                }
            }
        }
        if( e == -1 ) {
            // 从u邻接的结点中找一个距离汇点最近的点
            int minDist = MAXN; 
            for(e = head[u]; e != -1; e = E[e].next) {
                if ( E[e].cap ) {
                    int v = E[e].to;
                    if( dist[v] < minDist ) {
                        minDist = dist[v];
                        newhead[u] = e;
                    }
                }
            }
            // 更新这个最近的点 
            dcnt[ dist[u] ] --;
            dist[u] = minDist + 1;
            dcnt[ dist[u] ] ++;
            if( u != start ) {
                u = E[ stack[--top] ].from;
            }
        }else {
            // (u, edge[e].to) 为一条可行弧
            newhead[u] = e;
            stack[ top++ ] = e;
            u = E[e].to;
        }
    } 
    return maxflow;   
}


class infos {
public:
    int rcnt, ccnt;
    infos() {
        rcnt = ccnt = -1;
    }

    bool is_empty() {
        return rcnt == INF;
    }

    bool has_rowsum() {
        return rcnt != -1 && rcnt != INF;
    }

    bool has_colsum() {
        return ccnt != -1 && ccnt != INF;
    }

    bool row_black() {
        return has_rowsum() || rcnt == -1;
    }

    bool col_black() {
        return has_colsum() || ccnt == -1;
    }   

}v[110][110];


int N, M;
char str[1000];
int getNode(int idx, int r, int c) {
    return N*M*idx + r*M + c + 2;
}

int main() {
    int i, j, k;
    
    while( scanf("%d %d", &N, &M) != EOF ) {
        init();
        n = getNode(1, N-1, M-1) + 1;
        int S = 0, T = 1;
        
        for(i = 0; i < N; i++) {
            for(j = 0; j < M; j++) {
                v[i][j] = infos();
                
                scanf("%s", str);
                //strcpy(str, ".......");
                int x;
                if( str[3] == '\\' ) {
                    if( str[0] != 'X' ) {
                        sscanf(str, "%d", &x);
                        v[i][j].ccnt = x;
                    }
                    
                    if( str[4] != 'X' ) {
                        sscanf(&str[4], "%d", &x);
                        v[i][j].rcnt = x;
                    }
                }else if( str[3] == '.' ) {
                    v[i][j].rcnt = INF;
                }
            }
        }
        
        for(i = 0; i < N; i++) {
            for(j = 0; j < M; j++) {

                if( v[i][j].has_rowsum() ) {
                    for(k = j+1; k < M; k++) {
                        if( !v[i][k].is_empty() ) break;
                        addEdge( getNode(0, i, j), getNode(0, i, k), 8 );
                    }
                    addEdge( S, getNode(0, i, j), v[i][j].rcnt - (k-j-1) );
                }

                if( v[i][j].has_colsum() ) {
                    for(k = i+1; k < N; k++) {
                        if( !v[k][j].is_empty() ) break;
                        addEdge( getNode(0, k, j), getNode(1, i, j), 8 );
                    }
                    addEdge( getNode(1, i, j), T, v[i][j].ccnt - (k-i-1) );    
                }

                if( v[i][j].is_empty() ) {
                    for(k = j-1; k >= 0; k--) {
                        if( v[i][k].col_black() ) break;
                    }
                    if(k == -1 || v[i][k].rcnt == -1) {
                        addEdge( S, getNode(0, i, j), 8 );
                    }

                    for(k = i-1; k >= 0; k--) {
                        if( v[k][j].row_black() ) break;
                    }
                    if(k == -1 || v[k][j].ccnt == -1) {
                        addEdge( getNode(0, i, j), T, INF );
                    }
                }
            }
        }
        int ans = sap(S, T);

        for(i = 0; i < N; i++) {
            for(j = 0; j < M; j++) {
                if(j) printf(" ");
                if( v[i][j].is_empty() ) {
                    int s = 0;
                    for(k = head[ getNode(0, i, j) ]; k != -1; k = E[k].next) {
                        if( (k&1) ) {
                           s += E[k].cap + 1;
                        }
                    }
                    printf("%d", s );
                }else {
                    printf("_");
                }
            }
            puts("");
        }   
    }
    return 0;
}

/*
6 6
XXXXXXX XXXXXXX 028\XXX 017\XXX 028\XXX XXXXXXX
XXXXXXX 022\022 ....... ....... ....... 010\XXX
XXX\034 ....... ....... ....... ....... .......
XXX\014 ....... ....... 016\013 ....... .......
XXX\022 ....... ....... ....... ....... XXXXXXX
XXXXXXX XXX\016 ....... ....... XXXXXXX XXXXXXX

_ _ _ _ _ _
_ _ 5 8 9 _
_ 7 6 9 8 4
_ 6 8 _ 7 6
_ 9 2 7 4 _
_ _ 7 9 _ _
_ _ _ _ _ _ 

2 2
XXXXXXX XXXXXXX
XXX\009 .......

2 2
XXXXXXX 004\XXX
XXXXXXX .......

3 6
XXXXXXX XXXXXXX 006\XXX 007\XXX 009\XXX XXXXXXX
XXXXXXX 005\011 ....... ....... ....... 006\XXX
XXX\022 ....... ....... ....... XXXXXXX .......
*/



