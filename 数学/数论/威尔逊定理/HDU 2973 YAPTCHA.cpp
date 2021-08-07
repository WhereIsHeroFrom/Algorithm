#include <iostream>
#include <cstring>
using namespace std;

#define MAXP 3000008
#define LL __int64

//int primes[MAXP];
bool notprime[MAXP];

void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    //primes[0] = 0;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            //primes[++primes[0]] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for (LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

int s[1000010];

int main() {
    Eratosthenes();
    int i;
    s[0] = 0;
    for (i = 1; i <= 1000000; ++i) {
        if (!notprime[3 * i + 7]) {
            s[i] = s[i - 1] + 1;
        }
        else {
            s[i] = s[i - 1] + 0;
        }
    }
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", s[n]);
    }
    return 0;
}
