#include <iostream>

using namespace std;

#define LL __int64

LL gcd(LL a, LL b) {
    return b ? gcd(b, a%b) : a;
}

// aX + bY = gcd(a, b) 求出满足条件的某个整数对(X, Y) 
LL Extend_Euclid(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = Extend_Euclid(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

int main() {
    int t;
    int N;
    LL A;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &N);
        for(A = 1; A < N; A++) {
            if( gcd(A, N) > 1 ) {
                continue;
            }
            LL X, Y;
            // N * X + (-A^2) * Y = 1
            LL gcd = Extend_Euclid(N, -A*A, X, Y);
            Y = (Y*gcd % N + N) % N;
            //printf("%I64d %I64d", A, Y);
            if( (A*A + Y) % N != 0 ) {
                break;
            }
        }
        printf("%s\n", (A == N) ? "YES" : "NO");
    }
    return 0;
} 
