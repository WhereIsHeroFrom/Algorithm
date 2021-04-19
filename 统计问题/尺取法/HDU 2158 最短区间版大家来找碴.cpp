#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)

const int maxn = 100010;
int a[maxn];
int n, m;
int has[maxn], val[maxn];

int solve(int t) {
    int ans = n;
    int s = 0, i = 1, j = 0;
    while (j < n) {
        ++j;
        if (++has[a[j]] == 1) {
            s += val[a[j]];
            while (s == t) {
                ans = min(ans, j - i + 1);
                if (--has[a[i]] == 0) {
                    s -= val[a[i]];
                }
                ++i;
            }
        }
    }
    return ans;
}

int main() {
    int t;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        
        while (m--) {
            for (int i = 0; i < n; ++i) {
                val[i] = 0;
                has[i] = 0;
            }
            int x, t = 0;
            scanf("%d", &x);
            while (x--) {
                int g;
                scanf("%d", &g);
                if (!val[g]) {
                    ++ val[g];
                    ++t;
                }
            }
            printf("%d\n", solve(t));
        }
    }
    return 0;
}
