#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable : 4996)

const int maxn = 5010;
char c[maxn];
int n;

int dist(int idx1, int idx2) {
    int v = (int)c[idx1] - (int)c[idx2];
    if (v < 0) {
        v = -v;
    }
    return v;
}

int solve(int k, int m, char *c) {
    int maxv = 0;
    int d = 0;
    int al = 0, ar = -1;
    int br = k, bl = k + 1;

    while (ar < bl) {
        ++ar;
        --bl;
        if (ar >= bl) {
            break;
        }
        d += dist(ar, bl);
        while (d > m) {
            d -= dist(al, br);
            ++al;
            --br;
        }
        maxv = max(maxv, ar - al + 1);
    }
    return maxv;
}

int getans(int n, int m) {
    int maxv = 0;
    for (int k = n - 1; k >= 0; --k) {
        int ans = solve(k, m, c);
        maxv = max(maxv, ans);
    }
    return maxv;
}

int main() {
    int t;
    int m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        scanf("%s", c);
        int n = strlen(c);
        int maxv = getans(n, m);
        for (int i = 0; i < n / 2; ++i) {
            swap(c[i], c[n - 1 - i]);
        }
        maxv = max(maxv, getans(n, m));
        printf("%d\n", maxv);
    }
    return 0;
}

/*
3
abc
1
abcabc
1
abcabc
2
*/

