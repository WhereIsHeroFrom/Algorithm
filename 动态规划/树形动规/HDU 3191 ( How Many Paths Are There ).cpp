#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100
#define LL __int64
#define INF 1000000000

class Edge {
public:
    int u, v, val;
    Edge() {}
    Edge(int _u, int _v, int _val) {
        u = _u;
        v = _v;
        val = _val;
    }
}; 

class ansInfo {
public:
    int min, secmin;
    LL mincnt, seccnt;
    ansInfo(){}
    ansInfo(int _m, int _secm, LL _mcnt, LL _seccnt) {
        min = _m;
        secmin = _secm;
        mincnt = _mcnt;
        seccnt = _seccnt;
    }
}ai[ MAXN ];

int n, m, s, e;
vector <Edge> vec[MAXN];
vector <Edge> inv[MAXN];

void addEdge(int u, int v, int val) {
    vec[u].push_back( Edge(u, v, val) );
    inv[v].push_back( Edge(v, u, val) );
}

ansInfo dfs(int u) {
    if(u == s) {
        return  ansInfo(0, INF, 1, 0);
    }
    if ( ai[u].mincnt != -1 ) {
        return ai[u];
    }
    
    ai[u].mincnt = 0;
    ai[u].seccnt = 0;
    ai[u].min = INF;
    ai[u].secmin = INF; 
    
    // 更新当前点的最短路 
    for(int i = 0; i < inv[u].size(); i++) {
        int prev = inv[u][i].v;
        int edgeval = inv[u][i].val;
        ansInfo pre = dfs( prev );
        if( pre.min + edgeval < ai[u].min ) {
            ai[u].min = pre.min + edgeval;
            ai[u].mincnt = pre.mincnt;
        }else if( pre.min + edgeval == ai[u].min ) {
            ai[u].mincnt += pre.mincnt;
        }
    }

    // 更新当前点的次短路 
    for(int i = 0; i < inv[u].size(); i++) {
        int prev = inv[u][i].v;
        int edgeval = inv[u][i].val;
        ansInfo pre = dfs( prev );
        if( pre.min + edgeval > ai[u].min ) {
            if( pre.min + edgeval < ai[u].secmin ) {
                ai[u].secmin = pre.min + edgeval;
                ai[u].seccnt = pre.mincnt;
            }else if( pre.min + edgeval == ai[u].secmin ) {
                ai[u].seccnt += pre.mincnt;
            }
        }
    }    
    
    // 还需要算上从前驱结点的次短路更新过来的情况 
    if( ai[u].seccnt != -1 ) {
        for(int i = 0; i < inv[u].size(); i++) {
            int prev = inv[u][i].v;
            int edgeval = inv[u][i].val;
            
            ansInfo pre = dfs( prev );
            
            if( pre.secmin + edgeval > ai[u].min ) {
                if( pre.secmin + edgeval < ai[u].secmin ) {
                    ai[u].secmin = pre.secmin + edgeval;
                    ai[u].seccnt = pre.seccnt;
                }else if( pre.secmin + edgeval == ai[u].secmin ) {
                    ai[u].seccnt += pre.seccnt;
                }
            }
        }         
    }     
    return ai[u];
    
}

int main() {
    int i;
    while( scanf("%d %d %d %d", &n, &m, &s, &e) != EOF ) {
        for(i = 0; i < n; i++) {
            vec[i].clear();
            inv[i].clear();
            ai[i].mincnt = -1;
            ai[i].seccnt = -1;
        }
        while(m--) {
            int u, v, z;
            scanf("%d %d %d", &u, &v, &z);
            addEdge(u, v, z);
        }
        ansInfo p = dfs(e);
        printf("%d %I64d\n", p.secmin, p.seccnt);
        
        if( p.secmin == INF ) { 
            while(1);
        }
    }
    return 0;
}

/*
3 3 0 1
0 2 5
0 1 4
1 2 2

3 3 0 2
0 2 5
0 1 4
1 2 2

11 17 0 10
0 1 1
0 2 1
0 3 1
0 4 1
1 5 1
2 5 1
3 6 1
2 6 1
3 7 1
4 7 1
5 8 1
6 8 1
6 9 1
7 9 1
8 10 1
9 10 1
0 10 1

*/

