#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int inf = 1e9;
const int maxn = 2010;
int n;
int a[maxn], b[maxn];
int f[maxn];

void init() {
    memset(f, -1, sizeof(f));
}

int dfs(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n < 0) {
        return inf;
    }

    int &val = f[n];
    if (val != -1) {
        return val;
    }
    val = inf;

    val = min(val, a[n] + dfs(n - 1));
    val = min(val, b[n] + dfs(n - 2));
    return val;
}

int main() {
    int i, j;
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (i = 2; i <= n; ++i) {
            scanf("%d", &b[i]);
        }
        dfs(n);

        int h = 8 + f[n] / 3600;
        int m = f[n] / 60 % 60;
        int s = f[n] % 60;

        if (h >= 12) {
            h -= 12;
            printf("%02d:%02d:%02d pm\n", h, m, s);
        }
        else {
            printf("%02d:%02d:%02d am\n", h, m, s);
        }

    }

    return 0;
}