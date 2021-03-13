#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

typedef char ValueType;
const int maxn = 1010;
const int mod = 1e9 + 7;
int f[maxn][maxn];

struct Level {
    int v, h;
    char c;
    Level(int _v, int _h, char _c) : v(_v), h(_h), c(_c) {}
};

vector <Level> L[maxn];

int getLCS(int hsize, ValueType *h, int vsize, ValueType *v) {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < maxn; ++i) {
        L[i].clear();
    }
    f[0][0] = 0;
    L[0].push_back(Level(0, 0, 0));

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
                L[lvl].push_back(Level(i, j, v[i]));
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
char stk[110], tmp[110];
vector <string> ans;

void dfs(int dep, int level, const Level& lv) {
    if (!level) {
        for (int i = 0; i < dep; ++i) {
            tmp[i] = stk[dep - 1 - i];
        }
        tmp[dep] = '\0';
        ans.push_back(tmp);
        return;
    }


    for (int i = 0; i < L[level - 1].size(); ++i) {

        if (L[level - 1][i].h >= lv.h || L[level - 1][i].v >= lv.v) {
            continue;
        }
        stk[dep + 1] = L[level - 1][i].c;
        dfs(dep + 1, level - 1, L[level - 1][i]);
    }

}

int main() {
    int len[2];
    int t;
    c = 0;

    while (scanf("%s %s", &s[0][1], &s[1][1]) != EOF) {

        len[0] = strlen(&s[0][1]);
        len[1] = strlen(&s[1][1]);
        for (int i = 0; i < maxn; ++i) {
            L[i].clear();
        }
        int lvl = getLCS(len[0], s[0], len[1], s[1]);
        ans.clear();
        for (int i = 0; i < L[lvl].size(); ++i) {
            stk[0] = L[lvl][i].c;
            dfs(0, lvl, L[lvl][i]);
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); ++i) {
            if (i && ans[i] == ans[i - 1]) continue;
            printf("%s\n", ans[i].c_str());
        }

    }
    return 0;
}

/*
10
GATCGTGAGC
AGTACG
*/