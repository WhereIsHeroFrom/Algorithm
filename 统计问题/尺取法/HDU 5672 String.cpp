#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)
#define ll long long

const int maxn = 1000010;
char c[maxn];
int n;
int has[256];

ll solve(char *str, int k) {
    ll ans = 0;
    int s = 0, i = 0, j = -1;
    int len = strlen(str);
    memset(has, 0, sizeof(has));
    while (j < len - 1) {
        ++j;
        ++has[str[j]];
        if (has[str[j]] == 1) {
            ++s;
        }
        while (s >= k) {
            ans += (len - j);
            if (--has[str[i]] == 0) {
                --s;
            }
            ++i;
        }
    }
    return ans;
}

int main() {
    int t, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", c);
        scanf("%d", &k);
        ll ans = solve(c, k);
        printf("%lld\n", ans);
    }
    return 0;
}

/*
3
abc
5
aaaba
8
hdugirls
*/
