#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 1010

int sqr(int x) {
    return x * x;
}

struct Point {
    int x, y;
    Point() {
        x = y = 0;
    }
    Point(int ix, int iy) : x(ix), y(iy) {}

    void read() {
        scanf("%d %d", &x, &y);
    }
    int dist_sqr(Point& other) {
        return sqr(x - other.x) + sqr(y - other.y);
    }
};

struct Circle{
    Point pt;
    int R;
    Circle(){}
    Circle(Point _pt, int _R) {
        pt = _pt;
        R = _R;
    }

    void read() {
        pt.read();
        scanf("%d", &R);
    }

    bool isTouch(Circle& other) {
        int dist_sqr = pt.dist_sqr(other.pt);
        return sqr(R-other.R) <= dist_sqr && dist_sqr <= sqr(R+other.R);
    }
    bool isInner(Circle& other) {
        if(R >= other.R) {
            return false;
        }
        int dist_sqr = pt.dist_sqr(other.pt);
        return dist_sqr < sqr(R-other.R);
    }

    bool isPointTouch(Point& point) {
        int dist_sqr = pt.dist_sqr(point);
        return dist_sqr == sqr(R);
    }

    bool isPointIn(Point& point) {
        int dist_sqr = pt.dist_sqr(point);
        return dist_sqr < sqr(R);
    }
};

int n;
Point ydn_pt, mon_pt;
int ydn_v[MAXN], mon_v[MAXN];
Circle C[MAXN];

vector <int> edge[MAXN];
int in[MAXN];
int dp[MAXN];

void addEdge(int u, int v) {
    edge[u].push_back(v);
    in[v]++;
}

struct State {
    // —≈µ‰ƒ»µ±«∞»¶£¨π÷ŒÔµ±«∞»¶
    int v;
    int step;
    State() {}
    State(int _v, int _s) : v(_v), step(_s) {}
    bool operator < (const State& other) const {
        return in[v] > in[v];
    }
};

int Max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int v) {
    if(dp[v] != -1) {
        return dp[v];
    }
    if(v == n+1) {
        return 0;
    }
    int i, sum = 0;
    for(i = 0; i < edge[v].size(); ++i) {
        int vv = edge[v][i];
        sum = Max(dfs(vv), sum);
    }
    return dp[v] = (sum + 1);
}

void read_data() {
    int i;
    scanf("%d", &n);
    ydn_pt = Point(0, 0);
    mon_pt.read();
    for(i = 0; i < n; i++) {
        C[i].read();
        /*C[i].pt = Point(0, 0);
        C[i].R = i+1;*/
        edge[i].clear();
    }
    // –Èƒ‚—≈µ‰ƒ»µƒ‘≤
    C[n] = Circle(ydn_pt, 0);
    edge[n].clear();

    // –Èƒ‚“∞π÷µƒ‘≤
    C[n+1] = Circle(mon_pt, 0);
    edge[n+1].clear();
    memset(in, 0, sizeof(in));
}

// n:—≈µ‰ƒ»£¨  n+1:“∞π÷
// ydn_v ∞¸Œß—≈µ‰ƒ»µƒ»¶ºØ∫œ£¨mon_v∞¸Œß“∞π÷µƒ»¶ºØ∫œ
//
//
void build_edge() {
    int i, j;
    // edge£∫—≈µ‰ƒ» -> “∞π÷
    addEdge(n, n+1);
    ydn_v[0] = mon_v[0] = 0;
    for(i = 0; i < n; i++) {
        if( C[i].isPointTouch(ydn_pt) || C[i].isPointTouch(mon_pt) ) {
            // —≈µ‰ƒ» ªÚ “∞π÷ ‘⁄‘≤…œ£¨Œﬁ”√£¨∫ˆ¬‘
            continue;
        }
        if( C[i].isPointIn(ydn_pt) && C[i].isPointIn(mon_pt) ) {
            // —≈µ‰ƒ» ∫Õ π÷ŒÔÕ¨ ±‘⁄‘≤ƒ⁄£¨Œﬁ”√£¨∫ˆ¬‘
            continue;
        }
        if( C[i].isPointIn(ydn_pt) ) {
            // —≈µ‰ƒ»‘⁄‘≤ƒ⁄
            ydn_v[ ++ydn_v[0] ] = i;
            // edge£∫—≈µ‰ƒ» -> »Œ“‚»¶
            addEdge(n, i);
        }else if( C[i].isPointIn(mon_pt) ) {
            // π÷ŒÔ‘⁄‘≤ƒ⁄
            mon_v[ ++mon_v[0] ] = i;
            // edge£∫»Œ“‚»¶ -> “∞π÷
            addEdge(i, n+1);
        }
    }

    // √∂æŸ—≈µ‰ƒ»µƒ»¶
    // edge£∫—≈µ‰ƒ»–°»¶ -> —≈µ‰ƒ»¥Û»¶
    for(i = 1; i <= ydn_v[0]; ++i) {
        int x = ydn_v[i];
        for(j = 1; j <= ydn_v[0]; ++j) {
            if(i == j) {
                continue;
            }
            int y = ydn_v[j];
            if( C[x].isInner(C[y]) ) {
                addEdge(x, y);
            }
        }
    }

    // edge£∫—≈µ‰ƒ»»¶ -> “∞π÷»¶
    for(i = 1; i <= ydn_v[0]; ++i) {
        int x = ydn_v[i];
        addEdge(x, n+1);
        for(j = 1; j <= mon_v[0]; ++j) {
            int y = mon_v[j];
            if(!C[x].isTouch(C[y])) {
                addEdge(x, y);
            }
        }
    }


    // √∂æŸπ÷ŒÔµƒ»¶
    // edge£∫¥Û»¶ -> –°»¶
    for(i = 1; i <= mon_v[0]; ++i) {
        int x = mon_v[i];
        addEdge(n, x);
        for(j = 1; j <= mon_v[0]; ++j) {
            if(i == j) {
                continue;
            }
            int y = mon_v[j];
            if( C[x].isInner(C[y]) ) {
                addEdge(y, x);
            }
        }
    }
}

int main() {
    int i, j, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        read_data();
        build_edge();
        memset(dp, -1, sizeof(dp));
        printf("Case %d: %d\n", ++cases, dfs(n) - 1);
    }
    return 0;
}

/*
12
10 1000 1000
0 0 1
0 0 2
0 0 3
0 0 4
0 0 5
1000 1000 1
1000 1000 2
1000 1000 3
1000 1000 4
1000 1000 4

1 1000 1000
0 0 1

1 1000 1000
1000 1000 1

1 1000 1000
500 500 1
*/
