#include <iostream>
#include <vector>
#include <queue>
using namespace std;


#define MAXN 1010
#define MAXM 100010
 
struct edge {
    int to, dist, cost;
    edge() {
    }
    edge(int _t, int _d, int _c) {
        to = _t;
        dist = _d;
        cost = _c;
    }
    
    void read() {
        scanf("%d %d %d", &to, &dist, &cost);
    }
    
    friend bool operator < (edge a, edge b) {
        if(a.dist == b.dist) {
            return a.cost > b.cost;
        }
        return a.dist > b.dist;
    }
};
vector <edge> vec[1010];
 
edge ans[MAXN];
int n, m;

void spfa(int s) {
    int i;
    for(i = 1; i <= n; i++) {
        ans[i] = edge(-1, -1, -1);
    }
    ans[s] = edge(-1, 0, 0);
    
    priority_queue <edge> Q;
    Q.push( edge(s, 0, 0) );
    
    while( !Q.empty() ) {
        edge now = Q.top();
        Q.pop();
        
        int from = now.to;
        int predist = now.dist;
        int precost = now.cost;
        
        for(i = vec[from].size()-1; i >= 0; i--) {
            edge e = vec[from][i];
            int to = e.to;
            int nextdist = e.dist + predist;
            int nextcost = e.cost + precost;
            
            if( ans[to].dist == -1 || nextdist < ans[to].dist ) {
                ans[to].dist = nextdist;
                ans[to].cost = nextcost;
                Q.push( edge(to, nextdist, nextcost) );
            }else if(nextdist == ans[to].dist && nextcost < ans[to].cost) {
                ans[to].cost = nextcost;
                Q.push( edge(to, nextdist, nextcost) );                
            }
        }
        
    }    
}

int main() {
    int i;
    while( scanf("%d %d", &n, &m) != EOF ) {
        if(!n && !m) break;
        for(i = 1; i <= n; i++) vec[i].clear();
        for(i = 0; i < m; i++) {
            int from;
            scanf("%d", &from);
            edge tmp;
            tmp.read();
            vec[from].push_back(tmp);
            
            int to = tmp.to;
            tmp.to = from;
            vec[to].push_back( tmp );
        }
        int s, t;
        scanf("%d %d", &s, &t);
        spfa(s);
        printf("%d %d\n", ans[t].dist, ans[t].cost);
    }
    return 0;
}
/*
3 2
1 2 5 6
2 3 4 5
1 3
*/
