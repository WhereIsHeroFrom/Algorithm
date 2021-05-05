#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)
const int maxn = 510;
#define ll long long
int MOD;
int num[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

// count, B, C, cap
int f[maxn][2][2][2];

int dfs(int n, bool b, bool c, int cap) {
    if (n == 0) {
        if (b && c && !cap) {
            return 1;
        }
        return 0;
    }
    if (n < 0) {
        return 0;
    }
    ll val = f[n][b][c][cap];
    if (val != -1) {
        return val;
    }
    val = 0;
    if (b && c) {
        if (cap) {
            return n == 2 ? 1 : 0;
        }
        else {
            return n == 0 ? 1 : 0;
        }
    }
    else if (c) {
        for (int bnum = 0; bnum < 10; ++bnum) {
            int tot = (bnum + cap);
            int anum = tot % 10;
            int capc = tot / 10;
            int remainMatches = n - num[bnum] - num[anum];
            val += dfs(remainMatches, 0, 1, capc);
            if (bnum) {
                val += dfs(remainMatches, 1, 1, capc);
            }
        }
    }
    else if (b) {
        for (int cnum = 0; cnum < 10; ++cnum) {
            int tot = (cnum + cap);
            int anum = tot % 10;
            int capc = tot / 10;
            int remainMatches = n - num[cnum] - num[anum];
            val += dfs(remainMatches, 1, 0, capc);
            if (cnum) {
                val += dfs(remainMatches, 1, 1, capc);
            }
        }
    }
    else {
        for (int bnum = 0; bnum < 10; ++bnum) {
            for (int cnum = 0; cnum < 10; ++cnum) {
                int tot = (bnum + cnum + cap);
                int anum = tot % 10;
                int capc = tot / 10;
                int remainMatches = n - num[bnum] - num[cnum] - num[anum];
                val += dfs(remainMatches, 0, 0, capc);
                if (bnum && cnum) {
                    val += dfs(remainMatches, 1, 1, capc);
                }
                if (bnum) {
                    val += dfs(remainMatches, 1, 0, capc);
                }
                if (cnum) {
                    val += dfs(remainMatches, 0, 1, capc);
                }
            }
        }
    }
    return f[n][b][c][cap] = val % MOD;
}

int main() {
    int t;
    int n, cas = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &MOD);
        memset(f, -1, sizeof(f));
        printf("Case #%d: %d\n", ++cas, dfs(n - 3, 0, 0, 0));
    }
    return 0;
}

/*
4
12 1000000007
17 1000000007
20 1000000007
147 1000000007

*/
