#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-8
#define MAXN 910
#define MAXM 600000
#define INF 1000000000.0
#define MAXQ 100000

int n, m, L, U;
int mat[MAXN][MAXN];

class Edge {
public:
    int u, v;
    double val;
    int next;
    Edge() {}
    Edge(int _u, int _v, double _val, int _next = -1) {
        u = _u;
        v = _v;
        val = _val;
        next = _next;
    }
}edges[MAXM];

int head[MAXN], tot;

void addEdge(int u, int v, double val) {
    edges[tot] = Edge(u, v, val, head[u]);
    head[u] = tot++;
}

int getV(int aorb, int idx) {
    return aorb * 410 + idx;
}

double d[MAXN];
int cnt[MAXN];
Edge Q[MAXQ];
int front, rear;
int r, c;

bool LT(double a, double b) {
    return ! (fabs(a-b)<eps) && a > b;
}

bool spfa() {
    int i, j;
    for(i = 0; i < MAXN; i++) {
        d[i] = -INF;
        cnt[i] = 0;
    }
    d[ getV(0, 1) ] = 0;
    front = rear = 0;
    Q[ rear++ ] = Edge(-1, getV(0, 1), 0);

    while( front != rear ) {
        Edge now = Q[front++];

        if(front >= MAXQ) {
            return false;
        }

        int u = now.v;
        cnt[u] ++;
        if(cnt[u] > 18) {
            return false;
        }
        for(int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            double val = edges[i].val;

            if( LT( now.val + val, d[v] ) ) {
                d[v] = now.val + val;
                Q[ rear++ ] = Edge(u, v, d[v]);
                if (rear >= MAXQ) {
                    rear = 0;
                }
            }
        }
    }
    for(i = 1; i <= r; i++) {
        //printf("r -> %lf\n", d[getV(0, i)]);
        if(d[getV(0, i)] < -INF+1) return false;
    } 
    for(i = 1; i <= c; i++) {
        //printf("c -> %lf\n", d[getV(0, i)]);
        if(d[getV(1, i)] < -INF+1) return false;
    }

    return true;
}

int main() {
    int i, j;
    while( scanf("%d %d %d %d", &r, &c, &L, &U) != EOF ) {
        
        memset(head, -1, sizeof(head));
        tot = 0;
        n = r + c + 10;

        double lgl = log(1.0*L);
        double lgu = log(1.0*U);

        for(i = 1; i <= r; i++) {
            for(j = 1; j <= c; j++) {
                scanf("%d", &mat[i][j]);
                //mat[i][j] = i*j;
                double lg = log(1.0*mat[i][j]);


                addEdge( getV(0, i), getV(1, j), lg - lgu + eps );
                addEdge( getV(1, j), getV(0, i), lgl - lg - eps );
            }
        }


        printf("%s\n", spfa() ? "YES" : "NO");
    }
    return 0;
}

/*
3 3 1 2
1 1 1
1 1 1
1 1 9
400 400 200 200
400 400 200 200
400 400 200 2000
400 400 200 201
400 400 200 200
400 400 200 20000
400 400 200 200
400 400 200 20000
400 400 200 2000
400 400 200 20000
400 400 200 200
*/
