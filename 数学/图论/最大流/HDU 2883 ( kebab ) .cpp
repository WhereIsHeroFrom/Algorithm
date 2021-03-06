#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000050 
 
const int MAXN = 13100;  // 最大点数 
const int MAXM = 800000; // 最大边数 


class Edge {
    public:
    short from, to;
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
    //printf("%d %d %d\n", u, v, c);
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

int m;
int N, M;

class kebab {
public:
    int s, e;
    int num, tim;
    
    void read() {
        scanf("%d %d %d %d", &s, &num, &e, &tim);
    }
}ke[ 300 ];

int timev[ 500 ], timesize;
int S = 0, T = 1;

int getKebabNode(int idx) {
    return 2 + idx;
}

int getTimeNode(int idx) {
    return 2 + N + idx;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}


int main() {
    int i, j;
    while(scanf("%d %d", &N, &M) != EOF) {
        // 将时间离散化 
        int timetmp = 0;
        for(i = 0; i < N; i++) {
            ke[i].read();
            timev[ timetmp++ ] = ke[i].s;
            timev[ timetmp++ ] = ke[i].e;
        }
        sort(timev, timev + timetmp);
        timesize = 1;
        for(i = 1; i < timetmp; i++) {
            if(timev[i] != timev[i-1]) {
                timev[ timesize++ ] = timev[i];
            }
        }
        
        /*for(i = 0; i < timesize; i++) {
            printf("%d ", timev[i]);
        }
        puts("");
        */
        
        init();
        n = getTimeNode(timesize);
        int totalTime = 0;
        for(i = 0; i < N; i++) {
            int c = ke[i].num * ke[i].tim;
            totalTime += c;
            addEdge(S, getKebabNode(i), c);
        }
        
        for(i = 0; i < N; i++) {
            for(j = 1; j < timesize; j++) {
                int t_st = Max(timev[j-1], ke[i].s);
                int t_en = Min(timev[j], ke[i].e);
                
                if(t_en - t_st > 0) {
                     addEdge( getKebabNode(i), getTimeNode(j), INF );
                }
            }
        }
        
        for(i = 1; i < timesize; i++) {
            addEdge( getTimeNode(i), T, M * (timev[i] - timev[i-1]) );
        }

        int maxFlow = sap(S, T);
        //printf("%d %d\n", maxFlow, totalTime);
        printf("%s\n", maxFlow == totalTime ? "Yes" : "No");
    }
    return 0;
    
}

/*
2 10
1 10 6 3
2 10 4 2

2 10
1 10 5 3
2 10 4 2

1 1
1 5 101 20

2 1
1 1 21 5
20 1 30 2

*/

