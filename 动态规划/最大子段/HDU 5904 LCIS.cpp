#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000010;

int has[maxn];
int cas[maxn], casn;
int n, a[maxn];
int m, b[maxn];
int dp[2][maxn];

void process(int size, int *arr, int *dp) {
    for (int i = 0; i < size; ++i) {
        dp[arr[i]] = dp[arr[i] - 1] + 1;
    }
}

void clear(int size, int *arr, int *dp) {
    for (int i = 0; i < size; ++i) {
        dp[arr[i]] = 0;
    }
}

int main() {
    int t;
    int i, j;
    casn = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        for (i = 0; i < m; ++i) {
            scanf("%d", &b[i]);
        }
        process(n, a, dp[0]);
        process(m, b, dp[1]);

        int ans = 0;
        for (i = 0; i < n; ++i) {
            int v = min(dp[0][a[i]], dp[1][a[i]]);
            ans = max(ans, v);
        }

        clear(n, a, dp[0]);
        clear(m, b, dp[1]);
        printf("%d\n", ans);
    }
    return 0;
}
/*
10
16 5
1 23 2 32 4 3 4 5 6 1 3 4 5 6 7 8
1 2 3 4 5

14 14
1 8 2 9 3 10 4 11 5 12 6 13 7 14
1 2 3 4 5 6 7 8 9 10 11 12 13 14

8 5
1 2 3 0 1 2 3 4
1 2 2 3 3

8 5
3 4 5 5 6 7 5 6
1 1 1 1 1

*/