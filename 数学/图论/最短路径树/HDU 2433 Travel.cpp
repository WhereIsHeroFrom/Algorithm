/*
题意：
    对于n(n<=100)个点，m(m<=3000)条边的网络图，求删除每条边后得到的图的两两间的最
短路的和。 
题解：
    最短路径树。
    对于每个点root，建立以root为根结点的最短路径树，可以用BFS来构造，由于边权为1，
每次第一次搜索到的点一定是最短的点，将每棵最短路径树上的边用hash数组保存下来。
root到所有点的最短路径和记录在sum[root]中。 
    枚举每条边E，初始化ans=0，对于每个点u：
    1) 如果E不在u的最短路径树上，那么E的删除不会影响u到其它点的最短路径总和，直接
ans += sum[u];
    2) 否则，对u求一次删掉边E的spfa，求出到所有点的最短路径，计算和累加到ans上。 
    
    枚举完所有以u为根结点的最短路径树后，ans就是所求删除E这条边后最短路径总和。
    
    由于在最短路径树上的边最多n-1条，即2) 最多执行n-1次，而1)执行时间为O(1)，所以
总的时间复杂度为O(n*n*m)。 
    存边采用前向星，自己模拟队列比STL的queue快。 
 
*/
#include <iostream>
using namespace std;

#define MAXN 110
#define MAXM 6010

class Edge {
public:
    int u, v;
    int next;
    Edge(){}
    Edge(int _u, int _v, int _n) {
        u = _u;
        v = _v;
        next = _n;
    }
}edges[MAXM];

class distInfo {
public:
    int to;
    int d;
    distInfo () {
    }
    distInfo(int _t, int _d) {
        to = _t;
        d = _d;
    }
};

int head[MAXN], tot;

void addEdge(int u, int v) {
    edges[ tot ] = Edge(u, v, head[u]);
    head[u] = tot ++;
}


int n, m;
int pre[MAXN][MAXN], edgeId[MAXN][MAXN], sum[MAXN];
bool edgeHash[MAXN][MAXM];
int deg[MAXN]; 
int d[MAXN];

distInfo Q[100000];
int front, rear; 

// 构造最短路径树 
void constructSPathTree(int root) {
    memset(d, -1, sizeof(d));
    d[root] = 0;
    front = rear = 0;
    Q[ rear++ ] = distInfo(root, 0);
    
    int i;
    while( front < rear ) {
        distInfo now = Q[ front++ ];
        
        int u = now.to;
        for( i = head[u]; i != -1; i = edges[i].next ) {
            int v = edges[i].v;
            if( d[v] == -1 ) {
                d[v] = d[u] + 1;
                
                pre[root][v] = u;
                edgeId[root][v] = i;
                
                Q[rear++] = distInfo(v, d[v]);
            }
        }
    }
    
    sum[root] = 0;
    for(i = 1; i <= n; i++) {
        if( d[i] == -1 ) {
            sum[ root ] = -1;
            return ;
        }
        sum[ root ] += d[i];
    }
    
    // hash边
    // 表示 这条边是在最短路径树上的 
    for(i = 1; i <= n; i++) {
        if(i != root) {
            // 双向边 
            edgeHash[root][ edgeId[root][i] ] = 1;
            edgeHash[root][ edgeId[root][i]^1 ] = 1;
        }
    }
}

bool isInSPathTree(int root, int edgeID) {
    return edgeHash[root][edgeID];
}


int getSPathSum(int cutedge, int root) {
    memset(d, -1, sizeof(d));
    d[root] = 0;
    front = rear = 0;
    Q[ rear++ ] = distInfo(root, 0);
    
    int i;
    while( front < rear ) {
        distInfo now = Q[ front++ ];

        int u = now.to;
        for( i = head[u]; i != -1; i = edges[i].next ) {
            if(i == cutedge || i == (cutedge^1) ) {
                continue;
            }
            
            int v = edges[i].v;
            if( d[v] == -1 ) {
                d[v] = d[u] + 1;
                Q[rear++] = distInfo(v, d[v]);
            }
        }
    }
    
    int s = 0;
    for(i = 1; i <= n; i++) {
        if( d[i] == -1 ) {
            s = -1;
            return s;
        }
        s += d[i];
        //printf("%d %d %d\n", root, i, d[i]);
    }
    return s;
}

int main() {
    int i, j;
    while( scanf("%d %d", &n, &m) != EOF ) {
        memset( head, -1, sizeof(head) );
        memset( deg, 0, sizeof(deg) );
        tot = 0;
        
        for(i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge(x, y);
            addEdge(y, x);
            deg[x]++;
            deg[y]++;
        }
        
        for(i = 1; i <= n; i++) {
            for(j = 0; j < tot; j++) {
                edgeHash[i][j] = 0;
            }
            constructSPathTree(i);
            //printf("%d\n", sum[i]);
        }
        
        for(i = 0; i < m; i++) {
            int ans = 0;
            int edgeid = 2*i;
            for(j = 1; j <= n; j++) {
                if( deg[ edges[edgeid].u ] == 1 || deg[ edges[edgeid].v ] == 1 ) {
                    ans = -1;
                    break;
                }
                
                if( !isInSPathTree(j, edgeid) ) {
                    if(sum[j] == -1) {
                        ans = -1;
                        break;
                    }
                    ans += sum[j];
                }else {
                    int v = getSPathSum(edgeid, j);
                    if(v == -1) {
                        ans = -1;
                        break;
                    }else {
                        ans += v;
                    }
                }
            }
            
            if(ans == -1) printf("INF\n");
            else printf("%d\n", ans);
        }
        
    }
    return 0;
}

/*
5 5
1 2
2 3
3 4
4 5
5 1
*/

