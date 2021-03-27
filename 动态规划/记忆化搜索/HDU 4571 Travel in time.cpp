#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int inf = -1;
const int maxn = 110;

int mat[maxn][maxn];
int cost[maxn], s[maxn];
int f[maxn][310];
int ST, EN;
int S, E;

vector <int> vec[maxn];

void init() {
    memset(mat, inf, sizeof(mat));
    memset(f, inf, sizeof(f));
}

int Min(int a, int b) {
    if (a == inf) return b;
    if (b == inf) return a;
    return a < b ? a : b;
}

void floyd(int N) {
    int i, j, k;
    for (i = 0; i <= EN; ++i) mat[i][i] = 0;
    for (k = 0; k <= EN; ++k) {
        for (i = 0; i <= EN; ++i) {
            for (j = 0; j <= EN; ++j) {
                if (mat[i][k] != inf && mat[k][j] != inf)
                    mat[i][j] = Min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
    for (i = 1; i <= N; ++i) {
        vec[i].clear();
        for (j = 1; j <= N; ++j) {
            if (i != j) {
                if (s[j] < s[i] && mat[j][i] != inf) {
                    vec[i].push_back(j);
                }
            }
        }
    }
    vec[EN].clear();
    for (i = 0; i <= N; ++i) {
        if (mat[EN][i] != inf) {
            vec[EN].push_back(i);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (mat[i][ST] != inf) {
            vec[i].push_back(ST);
        }
    }

}

int dfs(int u, int t) {
    if (t < 0) {
        return INT_MIN;
    }
    if (u == ST) {
        if (t == 0) {
            return 0;
        }
        return INT_MIN;
    }

    int &val = f[u][t];
    if (val != inf) {
        return val;
    }
    val = INT_MIN;
    int tmpval;

    for (int i = 0; i < vec[u].size(); ++i) {
        int v = vec[u][i];

        // u 这个点选择的情况
        tmpval = s[u] + dfs(v, t - mat[u][v] - cost[u]);
        val = max(val, tmpval);
    }

    return val;

}

int main() {
    int t;
    int i, j;
    int N, M, T;
    int cas = 0;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d %d", &N, &M, &T, &S, &E);
        ++S, ++E;
        init();
        ST = 0;
        EN = N + 1;
        cost[ST] = cost[EN] = 0;
        s[ST] = s[EN] = 0;

        for (i = 1; i <= N; ++i) {
            scanf("%d", &cost[i]);
        }
        for (i = 1; i <= N; ++i) {
            scanf("%d", &s[i]);
        }
        mat[ST][S] = mat[S][ST] = 0;
        mat[EN][E] = mat[E][EN] = 0;

        while (M--) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            ++a, ++b;
            mat[a][b] = Min(mat[a][b], c);
            mat[b][a] = Min(mat[b][a], c);
        }
        floyd(N);
        int Max = 0;
        for (int i = 0; i <= T; ++i) {
            int ans = dfs(EN, i);
            Max = max(Max, ans);
        }
        printf("Case #%d:\n%d\n", ++cas, Max);

    }

    return 0;
}

/*
10
4 4 22 0 3
1 1 1 1
5 7 9 12
0 1 0
0 1 1
0 1 2
0 1 3

4 4 1 0 3
0 0 0 0
5 7 9 12
0 1 0
2 1 2
2 3 0
3 0 2
*/