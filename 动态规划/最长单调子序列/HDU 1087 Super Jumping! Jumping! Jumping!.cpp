#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long
#define maxn 1010

int a[maxn];
ll dp[maxn];

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n) {
        dp[0] = 0;
        ll allMax = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            int Max = 0;
            for (int j = 0; j < i; ++j) {
                if (a[j] < a[i] && dp[j] > Max) {
                    Max = dp[j];
                }
            }
            dp[i] = Max + a[i];
            allMax = max(allMax, dp[i]);
        }
        printf("%lld\n", allMax);

    }
    return 0;
}