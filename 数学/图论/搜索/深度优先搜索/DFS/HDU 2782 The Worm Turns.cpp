#include <iostream>

using namespace std;

char str[4] = { 'E', 'N', 'S', 'W' };

int dir[4][2] =
{
    { 0, 1 },
    { -1, 0 },
    { 1, 0 },
    { 0, -1 }
};

int n, m;
bool hash[627][627];
int k;


struct point {
    int x;
    int y;
    int Dir;
    int step;
}Max, buf;

void dfs(int x, int y, int Dir, int num) {

    int i;
    point tt;
    tt.x = x + dir[Dir][0];
    tt.y = y + dir[Dir][1];

    if (num + 1 > Max.step) {
        Max.step = num + 1;
        Max.Dir = buf.Dir;
        Max.x = buf.x;
        Max.y = buf.y;
    }

    if (tt.x < 0 || tt.y < 0 || tt.x == n || tt.y == m || hash[tt.x][tt.y]) {
        if (num == 0) {
            return;
        }
        for (i = 0; i < 4; i++) {
            if (i == Dir)
                continue;
            tt.x = x + dir[i][0];
            tt.y = y + dir[i][1];

            if (tt.x < 0 || tt.y < 0 || tt.x == n || tt.y == m || hash[tt.x][tt.y])
                continue;
            hash[tt.x][tt.y] = true;
            dfs(tt.x, tt.y, i, num + 1);
            hash[tt.x][tt.y] = false;
        }
    }
    else {
        hash[tt.x][tt.y] = true;
        dfs(tt.x, tt.y, Dir, num + 1);
        hash[tt.x][tt.y] = false;
    }
}

int main() {

    int x, y;
    int i, j, k;
    int t = 1;

    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {

        memset(hash, 0, sizeof(hash));
        scanf("%d", &k);
        for (i = 0; i < k; i++) {
            scanf("%d %d", &x, &y);
            hash[x][y] = true;
        }

        Max.step = 0;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (hash[i][j])
                    continue;
                buf.x = i;
                buf.y = j;
                for (k = 0; k < 4; k++) {
                    buf.Dir = k;
                    hash[i][j] = true;
                    dfs(i, j, k, 0);
                    hash[i][j] = false;
                }
            }
        }
        printf("Case %d: %d %d %d %c\n", t++, Max.step, Max.x, Max.y, str[Max.Dir]);
    }
}