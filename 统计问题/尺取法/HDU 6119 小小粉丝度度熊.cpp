#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#pragma warning(disable : 4996)

const int maxn = 100010;
int n;
int sum[maxn];

struct Interval {
    int l, r;

    Interval() {
        l = r = 0;
    }
    Interval(int _l, int _r) : l(_l), r(_r) {}

    bool operator < (const Interval& o) {
        return l < o.l;
    }
}S[maxn], T[maxn];

void process(int& n) {
    sort(S, S + n);
    int tmp = 0;
    int prel = S[0].l, prer = S[0].r;
    for (int i = 1; i < n; ++i) {
        if (S[i].l <= prer + 1) {
            prer = max(prer, S[i].r);
        }
        else {
            T[++tmp] = Interval(prel, prer);
            prel = S[i].l, prer = S[i].r;
        }
    }
    T[++tmp] = Interval(prel, prer);
    n = tmp;
    sum[0] = sum[1] = 0;
    for (int i = 2; i <= n; ++i) {
        sum[i] = sum[i - 1] + T[i].l - T[i - 1].r - 1;
    }
}

int solve(int n, int m) {
    int ans = 0;
    int s = 0, i = 1, j = 0;
    while (j < n) {
        ++j;
        while (sum[j] - sum[i] > m) {
            ++i;
        }
        
        ans = max(ans, T[j].r - T[i].l + 1 +  m-(sum[j] - sum[i]) );
    }
    return ans;
}

int main() {
    int t;
    int m;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) {
            int l, r;
            scanf("%d %d", &l, &r);
            S[i] = Interval(l, r);
        }
        process(n);
        printf("%d\n", solve(n, m));
    }
    return 0;
}

/*
2 1
1 1
3 3

1 2
1 1

5 0
2 12
3 3
5 5
7 9
13 16
*/
