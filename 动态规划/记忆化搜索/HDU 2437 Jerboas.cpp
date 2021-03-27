#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int next;
    int val;
};

vector < edge > vec[1010];

int dp[1010][1010];
char str[1010];
int n, m, s, k;

int dfs(int x, int mod) {
    if (x == s) {
        if (mod)
            return 1000000000;
        else
            return 0;
    }

    int i, j;
    int size = vec[x].size();
    int sum = 1000000000;
    for (i = 0; i < size; i++) {
        edge last = vec[x][i];
        int val = (mod - last.val) % k;
        if (val < 0)
            val += k;
        if (dp[last.next][val] == -1)
            dp[last.next][val] = dfs(last.next, val);
        if (dp[last.next][val] + last.val < sum)
            sum = dp[last.next][val] + last.val;
    }
    return sum;
}

int main() {
    int t;
    int x, y, z;
    int i, j;

    scanf("%d", &t);
    int ty = t;
    while (t--) {
        scanf("%d %d %d %d", &n, &m, &s, &k);
        for (i = 1; i <= n; i++) {
            for (j = 0; j < k; j++) {
                dp[i][j] = -1;
            }
            vec[i].clear();
        }
        scanf("%s", str);
        while (m--) {
            scanf("%d %d %d", &x, &y, &z);
            edge temp;
            temp.next = x;
            temp.val = z;
            vec[y].push_back(temp);
        }

        printf("Case %d:", ty - t);
        int Max = 1000000000;
        int u = -1;
        for (i = 1; i <= n; i++) {
            if (dp[i][0] == -1)
                dp[i][0] = dfs(i, 0);
            //printf("%d\n", dp[i][0]);

            if (dp[i][0] < Max && str[i - 1] == 'P') {
                Max = dp[i][0];
                u = i;
            }
        }

        if (u == -1)
            printf(" -1 -1\n");
        else
            printf(" %d %d\n", Max, u);

    }
    return 0;
}