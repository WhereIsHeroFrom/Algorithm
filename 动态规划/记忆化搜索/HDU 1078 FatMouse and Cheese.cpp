#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 110;
const int dir[4][2] = {
    { 0, 1 },
    { 0, -1 },
    { 1, 0 },
    { -1, 0 }
};


int n, k;
int mat[maxn][maxn];
int f[maxn][maxn];
int walkdir[maxn][maxn][4][maxn];

void init() {
    memset(f, -1, sizeof(f));
    memset(walkdir, 0, sizeof(walkdir));
}


int dfs(int x, int y) {
    if (x < 0 || x >= n) {
        return INT_MIN;
    }
    if (y < 0 || y >= n) {
        return INT_MIN;
    }
    if (!x && !y) {
        return f[x][y] = mat[x][y];
    }

    int &val = f[x][y];
    if (val != -1) {
        return val;
    }
    val = INT_MIN;
    for (int i = 0; i < 4; ++i) {
        for (int kk = 1; kk <= k; ++kk) {
            if (walkdir[x][y][i][kk] == 0) {
                continue;
            }
            int pre = dfs(x + kk * dir[i][0], y + kk * dir[i][1]);
            if (mat[x + kk * dir[i][0]][y + kk * dir[i][1]] < mat[x][y]) {
                val = max(val, pre + mat[x][y]);

            }
        }
    }
    return val;
}

int main() {
    int i, j;
    while (scanf("%d %d", &n, &k) != EOF && (n != -1 || k != -1)) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                scanf("%d", &mat[i][j]);
            }
        }
        init();

        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                for (int tt = 0; tt < 4; ++tt) {
                    for (int kk = 1; kk <= k; ++kk) {
                        int pi = i + kk * dir[tt][0];
                        int pj = j + kk * dir[tt][1];
                        if (pi < 0 || pi >= n || pj < 0 || pj >= n) break;

                        if (mat[pi][pj] < mat[i][j]) {
                            walkdir[i][j][tt][kk] = 1;
                        }
                    }
                }
            }
        }

        int Max = INT_MIN;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                int ans = dfs(i, j);
                Max = max(ans, Max);
            }
        }
        printf("%d\n", Max);
    }

    return 0;
}