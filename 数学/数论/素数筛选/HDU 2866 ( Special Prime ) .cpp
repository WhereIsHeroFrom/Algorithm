#include <iostream>
#include <cstring>
using namespace std;


#define MAXP 1000010
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];
LL ans[MAXP];

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for(int i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            primes[ ++primes[0] ] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for(LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

int main() {
    Eratosthenes();
    LL n, m;
    for(LL i = 1; i < MAXP; i++) {
        LL p = 3*i*i + 3*i + 1;
        if( p < MAXP ) {
            if( !notprime[p] ) {
                ans[ ++ans[0] ] = p;
                //printf("%I64d %I64d\n", i, p);
            }
        }else {
            break;
        }
    }
    int L, i;
    while ( scanf("%d", &L) != EOF ) {
        for(i = 1; i <= ans[0]; i++ ) {
            if( ans[i] > L ) {
                break;
            }
        }
        if(i == 1) {
            printf("No Special Prime!\n");
            continue;
        }
        printf("%d\n",  i - 1);
    }
    return 0;
}
