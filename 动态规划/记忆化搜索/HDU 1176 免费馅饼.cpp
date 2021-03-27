#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100010;
int n, k;
int val[maxn][12];
int f[maxn][12];  // f[0][5] = 0;

void init() {
    memset(f, -1, sizeof(f));
    memset(val, 0, sizeof(val));
}

int dfs(int time, int pos) {
    if (time == 0) {
        if (pos == 5) {
            return 0;
        }
        return INT_MIN;
    }
    if (pos < 0 || pos > 10) {
        return INT_MIN;
    }

    int &x = f[time][pos];
    if (x != -1) {
        return x;
    }
    x = INT_MIN;
    x = max(x, dfs(time - 1, pos - 1));
    x = max(x, dfs(time - 1, pos));
    x = max(x, dfs(time - 1, pos + 1));
    x += val[time][pos];
    return x;
}

int main() {
    int i, j;
    while (scanf("%d", &n) != EOF && n) {
        int maxT = 0;
        init();
        for (i = 0; i < n; ++i) {
            int x, T;
            scanf("%d %d", &x, &T);
            ++val[T][x];
            maxT = max(maxT, T);
        }
        int ans = 0;
        for (i = 0; i <= 10; ++i) {
            ans = max(ans, dfs(maxT, i));
        }
        printf("%d\n", ans);
    }

    return 0;
}