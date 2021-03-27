#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int dir[4][2] = {
    { 0, 1 },
    { 1, 0 },
    { 0, -1 },
    { -1, 0 },
};

const int maxn = 30;
const int maxt = 6;
int mat[maxn][maxn];
int vis[maxt + 1][maxn][maxn];
int n, m;

void init() {
    memset(vis, -1, sizeof(vis));
}

int pack(int t, int x, int y) {
    return (t << 8) | (x << 4) | y;
}

void unpack(int val, int &t, int&x, int &y) {
    t = (val >> 8);
    x = ((val >> 4) & 0xf);
    y = (val & 0xf);
}

bool isValid(int x, int y) {
    if (x >= n || x < 0) return false;
    if (y >= m || y < 0) return false;
    if (mat[x][y] == 0) return false;
    return true;
}

int bfs(int maxT, int x, int y) {
    init();
    int t;
    int val = pack(maxT, x, y);
    queue <int> Q;
    Q.push(val);
    vis[maxT][x][y] = 0;

    while (!Q.empty()) {
        int val = Q.front();
        Q.pop();
        unpack(val, t, x, y);
        if (mat[x][y] == 3) {
            return vis[t][x][y];
        }

        for (int i = 0; i < 4; ++i) {
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            int tt = t - 1;
            if (!isValid(tx, ty)) {
                continue;
            }
            if (tt > 0) {
                if (mat[tx][ty] == 4) {
                    tt = maxT;
                }
                if (vis[tt][tx][ty] == -1) {
                    vis[tt][tx][ty] = vis[t][x][y] + 1;
                    Q.push(pack(tt, tx, ty));
                }
            }
        }
    }
    return -1;
}

int main() {
    int t;
    int i, j;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        int x, y;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                scanf("%d", &mat[i][j]);
                if (mat[i][j] == 2) {
                    x = i, y = j;
                }
            }
        }
        int ans = bfs(6, x, y);
        printf("%d\n", ans);
    }
    return 0;
}