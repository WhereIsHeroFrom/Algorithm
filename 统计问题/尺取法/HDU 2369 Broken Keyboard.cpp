#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)

const int maxn = 1000010;
char c[maxn];
int n, m;
int has[256];

int solve(int t, char *str) {
    n = strlen(str);
    int ans = 0;
    int s = 0, i = 1, j = 0;
    while (j < n) {
        ++j;
        if (++has[str[j]] == 1) {
            ++s;
            while (s > t) {
                if (--has[str[i]] == 0) {
                    --s;
                }
                ++i;
            }
        }
        ans = max(ans, j - i + 1);
    }
    return ans;
}

int main() {
    int t;
    while (scanf("%d", &m) != EOF && m) {
        getchar();
        gets(c);
        memset(has, 0, sizeof(has));
        printf("%d\n", solve(m, c));
    }
    return 0;
}
