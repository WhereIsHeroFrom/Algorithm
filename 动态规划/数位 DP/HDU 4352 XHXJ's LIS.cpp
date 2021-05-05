
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma warning(disable : 4996)
const int maxl = 20;
const int maxk = 11;
const int maxstate = 260;
#define ll long long

ll f[maxl][maxk][maxk][maxstate][2];

void init() {
}

ll nstate[maxk][maxstate];
ll p[maxk];

void pre_init(int len, int depth, int pre, ll val) {
    if (depth == 0) {
        nstate[len][++nstate[len][0]] = val;
        return;
    }
    for (int i = pre + 1; i <= 9; ++i) {
        pre_init(len, depth - 1, i, val * 10 + i);
    }
    p[0] = 1;
    for (int i = 1; i < maxk; ++i) {
        p[i] = p[i - 1] * 10;
    }
}

void pre() {
    nstate[0][0] = 0;
    nstate[0][++nstate[0][0]] = 0;

    for (int i = 1; i <= 10; ++i) {
        nstate[i][0] = 0;
        pre_init(i, i, -1, 0);
        sort(nstate[i] + 1, nstate[i] + 1 + nstate[i][0]);
    }
    return;
}

int findstate(int len, ll state) {
    int l = 1, r = nstate[len][0];
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (nstate[len][mid] == state) {
            return mid;
        }
        else if (state > nstate[len][mid]) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
}

ll dfs(int n, int len, ll state, int noleadingzero, int limit, int d[], int K) {

    if (n == 0) {
        return (len == K) ? 1 : 0;
    }

    int stateidx = findstate(len, state);
    ll sum = f[n][K][len][stateidx][noleadingzero];
    if (sum!=-1 && limit) {
        return sum;
    }
    sum = 0;
    int maxdigit = (limit ? 9 : d[n]);
    int digit[maxl];
    int curpos = len-1;
    for (int j = len - 1; j >= 0; --j) {
        digit[j] = (state / p[j]) % 10;
    }

    for (int i = 0; i <= maxdigit; ++i) {
        bool islimit = (i < maxdigit) || limit;
        bool isnoleadingzero = (i > 0) || noleadingzero;
        
        if (!noleadingzero) {
            // 说明前面一直没有出现过非0的数
            sum += dfs(n - 1, (i == 0 ? 0 : 1), i, isnoleadingzero, islimit, d, K);
            continue;
        }
        
        while (curpos >= 0 && i > digit[curpos]) {
            --curpos;
        }
        int pos = curpos;

        if (pos == -1) {
            sum += dfs(n - 1, len + 1, state * 10 + i, isnoleadingzero, islimit, d, K);
        }
        else {
            ll nextstate = state + p[pos] * i - p[pos] * digit[pos];
            sum += dfs(n - 1, len, nextstate, isnoleadingzero, islimit, d, K);
        
        }
    
    }
    if (limit) {
        f[n][K][len][stateidx][noleadingzero] = sum;
    }
    return sum;
}

ll ans(ll val, int K) {
    if (val == 0) {
        return K == 1 ? 1 : 0;
    }

    int stk[maxl];
    int n = 0;
    while (val) {
        stk[++n] = val % 10;
        val /= 10;
    }
    init();
    ll s = dfs(n, 0, 0, false, false, stk, K);
    return s;
}


int main() {
    pre();
    int t;
    ll L, R;
    int K, cas = 0;
    scanf("%d", &t);
    memset(f, -1, sizeof(f));
    while (t--) {
        scanf("%lld %lld %d", &L, &R ,&K);
        printf("Case #%d: %lld\n", ++cas, ans(R, K) - ans(L-1, K) );
    }
    return 0;
}
/*
11
123 321 2

139
*/
