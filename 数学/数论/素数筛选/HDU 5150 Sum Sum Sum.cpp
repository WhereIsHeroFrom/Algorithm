#include <iostream>

using namespace std;
#define ll __int64
#define MAXP 10010
int notprime[MAXP + 1];
int primes[MAXP];

void Eratosthenes() {
    notprime[0] = notprime[1] = true;
    primes[0] = 0;
    notprime[1] = false;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            // 注意整数乘积超过int32
            for (ll j = (ll)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

int n;
int a[MAXP];

int main() {
    Eratosthenes();

    while (scanf("%d", &n) != EOF) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (!notprime[a[i]]) {
                ans += a[i];
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}