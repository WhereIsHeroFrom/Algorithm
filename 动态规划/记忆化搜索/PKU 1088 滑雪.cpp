#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int dir[4][2] = {
    { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
};

const int maxn = 210;
const int flag = -10209321;
#define ll int
int n, m;
ll f[maxn][maxn];
int mat[maxn][maxn];
int d[maxn][maxn][5];

void init(int n, int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = flag;
            d[i][j][0] = 0;
        }
    }
}

ll dfs(int x, int y) {

    int &val = f[x][y];
    if (val != flag) {
        return val;
    }
    val = 1;
    for (int i = 1; i <= d[x][y][0]; ++i) {
        int dk = d[x][y][i];
        int tx = x + dir[dk][0];
        int ty = y + dir[dk][1];
        val = max(val, dfs(tx, ty) + 1);
    }
    return val;
}




int main() {
    int t, cas = 0;


    ll a, b;
    while (scanf("%d %d", &n, &m) != EOF) {
        init(n, m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &mat[i][j]);

            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int ti = i + dir[k][0];
                    int tj = j + dir[k][1];
                    if (ti == 0 || tj == 0 || ti>n || tj > n)
                        continue;
                    if (mat[i][j] > mat[ti][tj]) d[i][j][++d[i][j][0]] = k;
                }
            }
        }
        int Max = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                Max = max(Max, dfs(i, j));
            }
        }
        printf("%d\n", Max);
    }
    return 0;
}