/*
    并查集：顺序删边 转换成 逆序加边
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


const int MAXN = 254020;
const int MAXC = 506;

int fset[MAXN];

void init_set(int n) {
    for (int i = 0; i <= n; ++i) {
        fset[i] = i;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fx] = fy;
        return true;
    }
    return false;
}

int n, m;

int getId(int r, int c) {
    return r * m + c;
}

char ch[1010];
int Map[MAXC][MAXC];

struct Pair {
    int r, c;

    void read() {
        scanf("%d %d", &r, &c);
    }

}P[ MAXN ];

int Q;

int dir[4][2] = {
    { 0, 1 }, { 0, -1 }, { 1, 0 }, {-1, 0}
};

bool isOutBound(int r, int c) {
    return r < 0 || r >= n || c < 0 || c >= m;
}


int main() {
    int i, j, k;
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        memset(Map, 0, sizeof(Map));
        init_set(MAXN - 1);

        for (i = 0; i < n; ++i) {
            scanf("%s", ch);
            for (j = 0; j < m; ++j) {
                Map[i + 2][j] = ch[j] - '0';
            }
        }
        n += 4;


        scanf("%d", &Q);
        for (i = 1; i <= Q; ++i) {
            P[i].read();
            ++ Map[P[i].r + 2][P[i].c];
        }
        
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {

                if (Map[i][j]) continue;

                for (k = 0; k < 4; ++k) {
                    int ti = dir[k][0] + i;
                    int tj = dir[k][1] + j;
                    if (isOutBound(ti, tj) || Map[ti][tj]) continue;
                    union_set(getId(i, j), getId(ti, tj));
                    
                }
            }
        }

        for (i = Q; i >= 1; --i) {
            if (find_set(getId(0, 0)) == find_set(getId(n - 1, 0))) {
                break;
            }
            int r = P[i].r + 2;
            int c = P[i].c;
            --Map[r][c];

            if (Map[r][c]) continue;

            for (k = 0; k < 4; ++k) {
                int ti = dir[k][0] + r;
                int tj = dir[k][1] + c;
                if (isOutBound(ti, tj)) continue;
                if (!Map[ti][tj]) {
                    union_set(getId(r, c), getId(ti, tj));
                }
            }
        }

        if (i == 0) {
            if (find_set(getId(0, 0)) != find_set(getId(n - 1, 0))) {
                i = -1;
            }
        }

        printf("%d\n", i + 1);

    }

    return 0;
}