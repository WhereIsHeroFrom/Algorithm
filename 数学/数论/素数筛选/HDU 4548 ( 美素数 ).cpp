#include <iostream>

using namespace std;
#define ll __int64
#define MAXP 1000010
int notprime[MAXP+1];
int primes[MAXP];

void Eratosthenes() {
    notprime[0] = notprime[1] = true;
    primes[0] = 0;
    for(int i = 2; i < MAXP; i++) {
        if(!notprime[i]) {
            primes[ ++primes[0] ] = i;
            // 注意整数乘积超过int32
            for(ll j = (ll)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

int b_prime[MAXP+1];

int main() {
    Eratosthenes();
    for(int i = 2; i < MAXP; i++) {
        int s = 0, k = i;
        if(!notprime[i]) {        
            while(k) {
                s += k % 10;
                k /= 10;
            }
        }
        b_prime[i] = ((!notprime[i] && !notprime[s]) ? 1 : 0) + b_prime[i-1];
    }
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("Case #%d: %d\n", ++cases, b_prime[r] - b_prime[l-1]);
    }
    return 0;
}
