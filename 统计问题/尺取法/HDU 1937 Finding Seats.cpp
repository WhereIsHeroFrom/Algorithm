#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable : 4996)

const int maxn = 310;
int n, m, k;
char mat[maxn][maxn];
int sum[maxn][maxn], line[maxn];


int solve(int l, int r, int len, int s, int minv) {
    int i = 1, j = 0;
    int ans = -1;
    while (j < len) {
        ++j;
        int totsum = sum[r][j] - sum[l - 1][j] - sum[r][i - 1] + sum[l - 1][i - 1];
        while (totsum >= s) {
            if (ans == -1) ans = j - i + 1;
            ans = min(ans, j - i + 1);
            ++i;
            totsum = sum[r][j] - sum[l - 1][j] - sum[r][i - 1] + sum[l - 1][i - 1];
        }
    }
    return ans;
}

int main() {
    while (scanf("%d %d %d", &n, &m, &k) != EOF && (n || m || k)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", & mat[i][1]);
        }
        for (int i = 1; i <= n; ++i) {
            line[0] = 0;
            for (int j = 1; j <= m; ++j) {
                line[j] = line[j - 1] + (mat[i][j] == '.' ? 1 : 0);
                sum[i][j] = sum[i - 1][j] + line[j];
            }
        }
        int minv = 1000000000;
        for (int l = 1; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                int ans = solve(l, r, m, k, minv);
                if (ans == -1) continue;
                ans *= (r - l + 1);
                minv = min(minv, ans);
            }
        }
        printf("%d\n", minv);
    }
    return 0;
}

/*
3 5 5
...XX
.X.XX
XX...

5 6 7
..X.X.
.XXX..
.XX.X.
.XXX.X
.XX.XX
*/
