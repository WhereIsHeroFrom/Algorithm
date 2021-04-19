#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXP 10010
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for (LL j = (LL)i * i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}
int n;

int main() {
    Eratosthenes();
    while (scanf_s("%d", &n) != EOF && n) {
        int s = 0, i = 1, j = 0;
        int cnt = 0;
        while (j < primes[0]) {
            ++j;
            s += primes[j];
            while (s > n) {
                s -= primes[i];
                ++i;
            }
            if (s == n) {
                ++cnt;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}

