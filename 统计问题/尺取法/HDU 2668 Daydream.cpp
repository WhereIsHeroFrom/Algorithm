#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)

const int maxn = 10000010;
char c[maxn];
int n;
int h[256];

int solve(int n, char *str, int& l, int& r) {
    int ans = 0, i = 0, j = -1, len;
    memset(h, 0, sizeof(h));
    while (j++ < n - 1) {
        ++h[str[j]];
        while (h[str[j]] > 1) {
            --h[str[i]];
            ++i;
        }
        len = j - i + 1;
        if(len > ans)
            ans = len, l = i, r = j;
    	printf("[%d, %d]\n", i, j);
    }
    return ans;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", c);
        int l, r;
        int ans = solve(n, c, l, r);
        printf("%d %d %d\n", ans, l, r);
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
