#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef char ValueType;
const int maxn = 2010;
const int mod = 1e9 + 7;
int f[maxn][maxn];

struct Level {
    int v, h;
    Level(int _v, int _h) : v(_v), h(_h) {}

    bool operator < (const)
};

vector <Level> L[maxn];

int getLCS(int hsize, ValueType *h, int vsize, ValueType *v) {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < maxn; ++i) {
        L[i].clear();
    }
    f[0][0] = 0;
    L[0].push_back(Level(0, 0));

    for (int i = 1; i <= vsize; ++i) {
        for (int j = 1; j <= hsize; ++j) {
            if (v[i] == h[j]) {
                f[i][j] = f[i - 1][j - 1] + 1;
            }
            else {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            }

            int lvl = f[i][j];
            if (v[i] == h[j]) {
                L[lvl].push_back(Level(i, j));
            }
            //printf("%d", f[i][j]);
        }
        //puts("");
    }

    return f[vsize][hsize];
}

char s[2][maxn];
int dp[maxn][maxn];
int c;

int dfs(int level, const Level& lv) {
    if (!level) {
        return 1;
    }
    int &x = dp[lv.v][lv.h];
    if (x == -1) {
        x = 0;
        for (int i = 0; i < L[level - 1].size(); ++i) {

            if (L[level - 1][i].h >= lv.h || L[level - 1][i].v >= lv.v) {
                continue;
            }
            ++c;
            x += dfs(level - 1, L[level - 1][i]);
            if (x >= mod) x %= mod;
        }
    }
    return x;
}

int main() {
    int len[2];
    int t;
    c = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%s %s", &s[0][1], &s[1][1]);
        for (int i = 1; i < 1000; ++i) {
            s[0][i] = s[1][i] = 'a';
        }
        s[0][1000] = s[1][500] = '\0';

        len[0] = strlen(&s[0][1]);
        len[1] = strlen(&s[1][1]);
        int lvl = getLCS(len[0], s[0], len[1], s[1]);
        memset(dp, -1, sizeof(dp));
        int ans = 0;
        for (int i = 0; i < L[lvl].size(); ++i) {
            ans = (ans + dfs(lvl, L[lvl][i])) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
10
GATCGTGAGC
AGTACG
*/