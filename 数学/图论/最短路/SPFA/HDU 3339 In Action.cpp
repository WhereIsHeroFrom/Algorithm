#include iostream
#include vector
#include queue
using namespace std;

#define MAXN 120
#define INF 1000000000

class Edge {
    public
        int u, v, val;
    Edge(){}
    Edge(int _u, int _v, int _val) {
        u = _u;
        v = _v;
        val = _val;
    }
};


vector  Edge  vec[MAXN];

int n, m;
int cost[MAXN], w[MAXN];

void spfa(int start) {
    int i;
    for (i = 0; i = n; i++) {
        cost[i] = INF;
    }
    cost[start] = 0;
    queue Edge  Q;
    Q.push(Edge(-1, start, 0));

    while (!Q.empty()) {
        Edge now = Q.front();
        Q.pop();

        int u = now.v;
        for (i = 0; i vec[u].size(); i++) {
            int v = vec[u][i].v;
            int val = vec[u][i].val;
            if (now.val + val  cost[v]) {
                cost[v] = now.val + val;
                Q.push(Edge(u, v, cost[v]));
            }
        }
    }
}

int dp[100100];

int main() {
    int t;
    int i, j;
    scanf(%d, &t);
    while (t--) {
        scanf(%d %d, &n, &m);
        for (i = 0; i = n; i++) {
            vec[i].clear();
        }
        for (i = 0; i m; i++) {
            int x, y, z;
            scanf(%d %d %d, &x, &y, &z);
            vec[x].push_back(Edge(x, y, z));
            vec[y].push_back(Edge(y, x, z));
        }
        int sum = 0;
        for (i = 1; i = n; i++) {
            scanf(%d, &w[i]);
            sum += w[i];
        }
        for (i = 1; i = sum; i++) dp[i] = INF;
        spfa(0);

        dp[0] = 0;
        for (i = 1; i = n; i++) {
            for (j = sum; j = w[i]; j--) {
                if (dp[j - w[i]] + cost[i]  dp[j]) {
                    dp[j] = dp[j - w[i]] + cost[i];
                }
            }
        }
        int ans = INF;
        for (i = sum2 + 1; i = sum; i++) {
            printf(%d %dn, i, dp[i]);
            if (dp[i]  ans) ans = dp[i];
        }
        if (ans == INF) printf(impossiblen);
        else printf(%dn, ans);
    }
    return 0;
}