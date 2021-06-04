#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int Q;
    scanf("%d", &Q);
    while(Q--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        int ans = (l + r) % 9 * (r - l + 1) % 9 * 5 % 9;
        printf("%d\n", ans);
    }
    return 0;
}
