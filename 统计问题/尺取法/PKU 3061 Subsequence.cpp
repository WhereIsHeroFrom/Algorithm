#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100010;
int sum[maxn];
int n, p;

int getminlen(int n, int *sum) {
    int len = n + 1;
    int s = 0, i = 1, j = 0;
    while (j++ < n) {
        while (sum[j] - sum[i - 1] >= p) {
            len = min(len, j - i + 1);
            ++i;
        }
    }
    if (len == n + 1) len = 0;
    return len;
}

int main() {
    int t;
    scanf_s("%d", &t);

    while (t--) {
        scanf_s("%d %d", &n, &p);
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf_s("%d", &x);
            sum[i] = sum[i - 1] + x;
        }
        printf("%d\n", getminlen(n, sum));
    }
    return 0;
}
