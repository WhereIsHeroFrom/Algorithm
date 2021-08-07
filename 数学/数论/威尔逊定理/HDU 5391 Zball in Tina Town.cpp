#include <iostream>
#include <cstring>
using namespace std;

const int MAXP = 65536;
#define ll long long

int primes[MAXP];
bool notprime[MAXP];
 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < MAXP; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for(ll j = (ll)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

bool isPrime(int n) {
    if(n < MAXP) {
        return !notprime[n];
    }
    
    for(int i = 1; i <= primes[0]; ++i) {
        if(n % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int t, n;
    Eratosthenes();
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        if(n == 4) {
            printf("2\n");
        }else if( isPrime(n) ) {
            --n;
            printf("%d\n", n);
        }else {
            printf("0\n");
        }
    }
    
    
    return 0;
} 
