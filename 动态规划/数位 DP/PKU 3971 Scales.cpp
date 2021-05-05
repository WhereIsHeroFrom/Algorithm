#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma warning(disable : 4996)
const int maxl = 1000010;
const int maxd = 2;
const int mod = (1e9 + 7);
#define ll long long

short f[maxl][maxd];
short cas[maxl][maxd], C;
char d[maxl];
int N, L, D;

short dfs(int n, int cap, char d[]) {
    short &sum = f[n][cap];
    if (cas[n][cap] == C) {
        return sum;
    }
    if (n == 0) {
        if (cap == 0) {
            return 1;
        }
        return 0;
    }

    sum = 0;
    cas[n][cap] = C;
    for (int i = -1; i <= 1; ++i) {
        int val = (d[n]-'0') + cap;
        if ( (val + i) & 1 ) {
            continue;
        }
        int ncap = ( (val + i) >> 1 );
        sum += dfs(n - 1, ncap, d);
        if (sum >= D) sum %= D;
    }
    return sum;
}

void init() {
    ++C;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &N, &L ,&D);
        for (int i = 0; i < N - L; ++i) {
            d[1 + i] = '0';
        }
        scanf("%s", d + 1 + N-L);
        init();
        int ans = dfs(N, 0, d);
        printf("%d\n", ans);
    }
    return 0;
}
/*
1 0 10 10 3
2 0 100 10 1 4
1 0 10 2 1
*/
