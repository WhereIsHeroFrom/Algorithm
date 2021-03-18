#include <iostream>
#include <vector>
using namespace std;

int n, m;
int i, j;
int map[1001][1001];
vector < int > vec[1001];
int d[1001];
bool s[1001];
int dp[1001];

void Dijkstra() {
    int i;

    for (i = 1; i <= n; i++) {
        d[i] = map[2][i];
        s[i] = 0;
    }
    d[2] = 0;
    s[2] = 1;

    while (1) {
        int Min = INT_MAX, u = -1;

        for (i = 1; i <= n; i++) {
            if (!s[i] && d[i] < Min) {
                Min = d[i];
                u = i;
            }
        }

        if (u == -1)
            return;

        s[u] = 1;

        for (i = 1; i <= n; i++) {
            if (!s[i] && d[u] + map[u][i] < d[i]) {
                d[i] = d[u] + map[u][i];
            }
        }
    }
}

int dfs(int u) {

    int sum = 0;
    int i;

    if (u == 2)
        return 1;

    for (i = 0; i < vec[u].size(); i++) {

        int p = vec[u][i];

        if (d[p] < d[u]) {
            if (dp[p] == -1)
                dp[p] = dfs(p);
            sum += dp[p];
        }
    }
    return sum;
}
int main() {
    int x, y, c;
    while (scanf("%d %d", &n, &m) != EOF && n) {

        for (i = 1; i <= n; i++) {
            vec[i].clear();
        }
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                map[i][j] = 100000000;
            }
        }

        while (m--) {
            scanf("%d %d %d", &x, &y, &c);
            if (c < map[x][y]) {
                map[x][y] = map[y][x] = c;
                vec[x].push_back(y);
                vec[y].push_back(x);
            }
        }

        Dijkstra();



        memset(dp, -1, sizeof(dp));
        dp[1] = dfs(1);

        printf("%d\n", dp[1]);
    }
    return 0;
}