#include <iostream>

using namespace std;
#define ll __int64
#define MAXP 100010
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

int ans[MAXP];

int main() {
    Eratosthenes();
    int n;
    for(int i = 1; i + 2 < MAXP; ++i) {
    	int x = 0;
    	if( !notprime[i] && !notprime[i+2] ) {
    		x = 1;
		}
		ans [i+2] = ans[i+1] + x;
	}
	while(scanf("%d", &n) != EOF && n >= 0) {
		printf("%d\n", ans[n]);
	} 
    return 0;
}
