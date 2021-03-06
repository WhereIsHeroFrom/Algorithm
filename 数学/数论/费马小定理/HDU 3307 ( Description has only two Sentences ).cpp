#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define LL __int64
#define MAXN 65540

int f[MAXN], primes[MAXN], pcnt;

LL GCD(LL a, LL b) {
    if(!b) {
        return a;
    }
    return GCD(b, a%b);
}

LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

void primeFilter() {
    f[0] = f[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if( !f[i] ) {
            primes[ pcnt++ ] = i;
            for(int j = i+i; j < MAXN; j += i) {
                f[j] = 1;
            }
        }
    }
}

LL Euler(LL n) {
    if(n <= 1) {
        return n;
    }
    LL ans = 1;

    for(int i = 0; i < pcnt; i++) {
        if(n % primes[i] == 0) {
            n /= primes[i];
            ans *= (primes[i] - 1);
            while ( n % primes[i] == 0 ) {
                n /= primes[i];
                ans *= primes[i];
            }

            if(n == 1) {
                return ans;
            }
        }
    }
    if(n != 1) {
        ans *= (n - 1);
    }
    return ans;
}

vector<LL> getPrimeFactors(LL n) {
    vector<LL> ans;
    if(n == 1) {
        return ans;
    }
    for(int i = 0; i < pcnt; i++) {

        if(n % primes[i] == 0) {
            ans.push_back( primes[i] );
            while ( n % primes[i] == 0 ) {
                n /= primes[i];
            }

            if(n == 1) {
                return ans;
            }
        }
    }
    if(n != 1) {
        ans.push_back(n);
    }
    return ans;
}

LL Mod(LL a, LL b, LL mod) {
    if(!b) return 1 % mod;
    return Mod(a*a%mod, b/2, mod) * ( (b&1)?a:1 ) % mod;
}

int main() {
    primeFilter();
    LL X, Y, a0;
    while( scanf("%I64d %I64d %I64d", &X, &Y, &a0) != EOF ) {
        if(Y == 0) {
            printf("1\n");
        }else {
            LL K = Y / (X-1);
            LL G = GCD(a0, K);
            a0 /= G;
            if( GCD(a0, X) == 1 ) {
                LL euler = Euler(a0);
                double maxv = sqrt( euler * 1.0 );
                LL ans = euler;
                for(int i = 1; i <= maxv; i++) {
                    if( euler % i ) continue;

                    if( Mod(X, i, a0) == 1 ) {
                        ans = i;
                        break;
                    }
                    if( Mod(X, euler/i, a0) == 1 ) {
                        if( euler/i < ans ) {
                            ans = euler/i;
                        }
                    }
                }
                printf("%I64d\n", ans);
            }else {
                printf("Impossible!\n");
            }
        }
    }
    return 0;
}

