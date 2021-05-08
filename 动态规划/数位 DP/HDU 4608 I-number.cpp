#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;
#pragma warning(disable : 4996)


const int maxl = 20;
const int invalidstate = -123456789;
const int saturatedstate = 10;
const int leadingzerostate = 11;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isEndStateValid(stType state, bool lim) {
    return (state == 0) && lim;
}

stType nextState(stType st, int digit) {
    if (st == leadingzerostate) {
        if (digit == 0) {
            return leadingzerostate;
        }
        st = 0;
    }
    return (st + digit) % 10;
}

void init() {
    memset(f, inf, sizeof(f));
}

char stk[100010];

bool dfs(int n, int maxlen, stType state, bool lim, char d[]) {
    if (n == maxlen)
        return isEndStateValid(state, lim);
    //ll sum = f[n][state];
    //if (lim && sum != inf) return sum;
    //sum = 0;
    int minv = lim ? 0 : (d[n] - '0');
    for (int k = minv; k <= 9; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k > minv) || lim;
        if (invalidstate != st) {
            stk[n] = k + '0';
            if (dfs(n + 1, maxlen, st, nextlim, d)) {
                return true;
            }
        }
    }
    //if (lim) f[n][state] = sum;
    return false;
}


char c[100010];

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", c);
        int len = strlen(c);
        if (dfs(0, len, 0, false, c)) {
            stk[len] = '\0';
            puts(stk);
        }
        else {
            printf("1");
            for (int i = 0; i < len - 1; ++i) {
                printf("0");
            }
            printf("9\n");
        }

    }
    return 0;
}