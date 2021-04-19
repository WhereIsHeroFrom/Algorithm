#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)
#define ll long long

const int maxn = 2000010;
int a[maxn], sum[maxn];
int n;
int has[256];

int solve(int len, int maxlen, int *a) {
    int ans = 0;
    int maxv = 0;
    int s = 0, i = 1, j = 0;
    while (j < len - 1) {
        ++j;
        s += a[j];
        while (s < 0 || j - i + 1 > maxlen) {
            s -= a[i];
            ++i;
        }
        // (i, j) 为满足条件的一组解
        if (sum[j] - sum[i - 1] > maxv) {
            maxv = sum[j] - sum[i - 1];
            ans = i - 1;
        }
    }
    return ans;
}

int main() {
    int t, k;
    while (scanf("%d", &n) != EOF) {

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            a[n+i] = a[i];
        }

        int n2 = n * 2;
        for (int i = 1; i <= n2; ++i) {
            sum[i] = sum[i - 1] + a[i];
        }

        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            a[i] -= x;
            a[n + i] = a[i];
        }

        int ans = solve(n2, n, a);
        printf("%d\n", ans);
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
