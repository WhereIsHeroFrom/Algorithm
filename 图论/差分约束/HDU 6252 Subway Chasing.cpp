/*
题意：
    1 2 3 4 5 ... N 个地铁站，呈直线排列。并且地铁速度为匀速，两个玩家分别在两辆地铁上。
    A B 表示后面那个玩家的位置，当A==B则表示正好在第A个地铁站；当B=A+1，则表示在A到A+1的路上。
    C D 表示前面那个玩家的位置，当C==D则表示正好在第C个地铁站；当D=C+1，则表示在C到C+1的路上。
    给定两个玩家的时间差X，求从第i地铁站到第i+1地铁站的时间差（1 <= T <= 10^9）。

题解：
     差分约束
     令从第i个地铁站到第i+1个地铁站的时间差为T[i]，从第1个地铁站到第i个地铁站的加和为S[i] = T[1] + T[2] + ... T[i-1]
     
     那么可以列出一些不等式：
         1 <= Si - Si-1 <= 10^9
     并且 定义三元组G(x, y, z) 表示 S[x] - S[y] >= z 
        if(A == B) {
            if(C == D) {
                // S[C] - S[A] = X
                G(C, A, X)
                G(A, C, -X)
            }else {
                // S[C] - S[A] < X < S[D] - S[A]
                G(D, A, X+1);
                G(A, C, 1-X);
            }
        }else {
            if(C == D) {
                // S[D] - S[B] < X < S[D] - S[A]
                G(D, A, X+1);
                G(B, D, 1-X);
            }else {
                // S[C] - S[B] < X < S[D] - S[A]
                G(D, A, X+1);
                G(B, C, 1-X);
            }
        }
    
    对于三元组 G(x, y, z) 建边， y->x (权为z) 
    求一遍最长路 
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 4010
#define INF -1000000000
#define ll long long

struct edge {
    int from, to;
    ll val;
    int next;
    edge() {
    }
    edge(int _f, int _t, ll _v, int _n) {
        from = _f;
        to = _t;
        val = _v;
        next = _n;
    }
}E[MAXN*8];

int n;
ll dis[MAXN];
int visitCount[MAXN];
int head[MAXN], tot;

void spfa_init(int s) {
    int i;
    for(i = 0; i <= n; i++) {
        dis[i] = INF;
        visitCount[i] = 0;
    }
    dis[s] = 0;
}

// 返回是否存在环 
bool spfa(int s) {
    int i;
    spfa_init(s);
    queue <edge> Q;
    Q.push( edge(-1, s, 0, -1) );
    
    while( !Q.empty() ) {
        edge now = Q.front();
        Q.pop();
        
        int from = now.to;
        ll predist = now.val;
        //printf("!!!!! %d %lld\n", from, predist);
        
        if( visitCount[from]++ > n ) {
            return true;
        }
        
        for(i = head[from]; i != -1; i = E[i].next) {
            int to = E[i].to;
            ll nextdist = E[i].val + predist;
            
            if(dis[to] == INF || nextdist > dis[to]) {
                dis[to] = nextdist;
                Q.push( edge(from, to, nextdist, -1) );
            }
        }    
    }
    
    return false;
}

void edge_init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int c) {
    E[tot] = edge(u, v, c, head[u]);
    head[u] = tot++;
}

// 为满足S1 - S2 >= w的不等式建边 
void construct_edge(int S1, int S2, int w) {
    //printf(">>> %d %d %d\n", S2, S1, w);
    addEdge(S2, S1, w); 
}

int m, X;

int main() {
    int i;
    int t = 0, cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d %d %d", &n, &m, &X);
        edge_init();
        for(i = 2; i <= n; i++) {
            construct_edge(i-1, i, INF);
            construct_edge(i, i-1, 1);
        }
        while(m--) {
            int A, B, C, D;
            scanf("%d %d %d %d", &A, &B, &C, &D);
            if(A == B) {
                if(C == D) {
                    construct_edge(C, A, X);
                    construct_edge(A, C, -X);
                }else {
                    construct_edge(D, A, X+1);
                    construct_edge(A, C, 1-X);
                }
            }else {
                if(C == D) {
                    construct_edge(D, A, X+1);
                    construct_edge(B, D, 1-X);
                }else {
                    construct_edge(D, A, X+1);
                    construct_edge(B, C, 1-X);
                }
            }
        }
        int ret = spfa(1);
        printf("Case #%d:", ++t);
        if(!ret) {
            for(i = 2; i <= n; i++) {
                printf(" %d", dis[i]-dis[i-1]);
            }
        }else {
            printf(" IMPOSSIBLE");
        }
        puts("");
    }
    
    
    return 0;
}