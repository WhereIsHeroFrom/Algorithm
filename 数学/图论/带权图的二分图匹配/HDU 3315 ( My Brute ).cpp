#include <iostream>
#include <queue>

using namespace std;

const int N = 301; 
const int INF = 1 << 29; 

class Graph 
{ 
private: 
    bool xckd[N], yckd[N]; 
    int edge[N][N], xmate[N], ymate[N]; 
    int lx[N], ly[N], slack[N], prev[N]; 
    queue<int> Q; 
    bool bfs(); 
    void agument(int); 
public: 
    int n;
    bool make();  // edge建图, edge[i][j] 表示边i, j的建边情况
    int KMMatch(); 
}Gra; 

bool Graph::bfs() { 
    while(!Q.empty()) { 
        int p = Q.front(), u = p>>1; Q.pop(); 
        if(p&1) { 
            if(ymate[u] == -1) { agument(u); return true; } 
            else { xckd[ymate[u]] = true; Q.push(ymate[u]<<1); } 
        } else { 
            for(int i = 0; i < n; i++) 
                if(yckd[i]) continue; 
                else if(lx[u]+ly[i] != edge[u][i]) { 
                    int ex = lx[u]+ly[i]-edge[u][i]; 
                    if(slack[i] > ex) { slack[i] = ex; prev[i] = u; } 
                } else { 
                    yckd[i] = true; prev[i] = u; 
                    Q.push((i<<1)|1); 
                } 
        } 
    } 
    return false; 
} 
int v[ 100 ], h[ 100 ], p[ 100 ], a[ 100 ], b[ 100 ];

int val( int h, int p, int a, int b ) {
    while(1) {
        p -= a;
        if( p <= 0 ) return 1;
        h -= b;
        if( h <= 0 ) return -1;
    }
}

bool Graph:: make() {
    int i, j;
    for( i = 0; i < n; i ++ ) {
        for( j = 0; j < n; j++ ) {
            edge[i][j] = val( h[i], p[j], a[i], b[j] ) * v[i];
            edge[i][j] *= 2;
            if( i == j )
                edge[i][j] ++;
        }
    }
    return true;
}
void Graph::agument(int u) { 
    while(u != -1) { 
        int pv = xmate[prev[u]]; 
        ymate[u] = prev[u]; xmate[prev[u]] = u; 
        u = pv; 
    } 
} 
int Graph::KMMatch() 
{ 
    int i, j;
    memset(ly, 0, sizeof(ly)); 
    for(i = 0; i < n; i++) { 
        lx[i] = -INF; 
        for(j = 0; j < n; j++) 
            lx[i] =  lx[i] > edge[i][j] ? lx[i] : edge[i][j]; 
    } 
    memset(xmate, -1, sizeof(xmate)); memset(ymate, -1, sizeof(ymate)); 
    bool agu = true; 
    for(int mn = 0; mn < n; mn++) { 
        if(agu) { 
            memset(xckd, false, sizeof(xckd)); 
            memset(yckd, false, sizeof(yckd)); 
            for(i = 0; i < n; i++) slack[i] = INF; 
            while(!Q.empty()) Q.pop(); 
            xckd[mn] = true; Q.push(mn<<1); 
        } 
        if(bfs()) { agu = true; continue; } 
        int ex = INF; mn--; agu = false; 
        for(i = 0; i < n; i++) 
            if(!yckd[i]) ex = ex < slack[i] ? ex : slack[i]; 
            for(i = 0; i < n; i++) { 
                if(xckd[i]) lx[i] -= ex; 
                if(yckd[i]) ly[i] += ex; 
                slack[i] -= ex; 
            } 
            for(int i = 0; i < n; i++) 
                if(!yckd[i] && slack[i] == 0) { yckd[i] = true; Q.push((i<<1)|1); } 
    } 
    int cost = 0; 
    int u = 0;

    for(i = 0; i < n; i++) {
        if( i == xmate[i] ) {
            edge[i][ xmate[i] ] --;
            u ++;
        }
        edge[i][ xmate[i] ] /= 2;
        cost += edge[i][ xmate[i] ];
    }

    if( cost <= 0 )
        printf("Oh, I lose my dear seaco!\n");
    else {
        printf("%d %.3lf%%\n", cost, 100.0 * u / n );
    }
    return cost; 
}



int main() {
    int i;
    while( scanf( "%d", &Gra.n ) != EOF && Gra.n ) {
        for( i = 0; i < Gra.n; i ++ ) {
            scanf("%d", &v[i] );
        }
        for( i = 0; i < Gra.n; i ++ ) {
            scanf("%d", &h[i] );
        }
        for( i = 0; i < Gra.n; i ++ ) {
            scanf("%d", &p[i] );
        }
        for( i = 0; i < Gra.n; i ++ ) {
            scanf("%d", &a[i] );
        }
        for( i = 0; i < Gra.n; i ++ ) {
            scanf("%d", &b[i] );
        }
        Gra.make();
        Gra.KMMatch();

    }
    return 0;
}
