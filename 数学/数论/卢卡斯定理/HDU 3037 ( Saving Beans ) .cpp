#include <iostream>

#define LL __int64

LL exp_gcd(LL a, LL b, LL &X, LL &Y){

   LL q, temp;
     if(b == 0) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = exp_gcd(b, a % b, X, Y);
        temp = X; X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

LL GCD(LL a, LL b)
{
     LL m = 1;
     if( a == 0 )
         return b;
     if( b == 0 )
         return a;
     while(m) {
        m = a%b;
        a = b;
        b = m;
     }
     return a;
}

LL a[101], b[101];
int at, bt;
int n, m, p;
LL JieC[ 100000 ];

LL C( LL n, LL m ) {          // n, m < p 时的C(n, m)
    LL A, B;
    if( n < m )
        return 0;
    else if( n == m )
        return 1;

    A = JieC[n];
    B = (JieC[m] * JieC[n-m]) % p;
    
    LL G = GCD( A, B );

    if( G == 0 )
        return 1;
    
    A /= G;
    B /= G;

    LL X, Y;

    exp_gcd( B, p, X, Y);
    X %= p;
    if( X < 0 )
        X += p;
    return A * X % p; 
}

LL BigC( LL n, LL m, LL p ) {

    int i;
    memset( a, 0, sizeof( a ));
    memset( b, 0, sizeof( b ));
    at = 0; bt = 0;

    while( n ) {
        a[ at++ ] = n % p;
        n /= p;
    }
    while( m ) {
        b[ bt++ ] = m % p;
        m /= p;
    }

    int k = at > bt ? at : bt;

    int Max = 0;
    for(i = 0; i < k; i++) {
        if( a[i] > Max )
            Max = a[i];
        if( b[i] > Max )
            Max = b[i];
    }

    JieC[0] = 1;
    for(i = 1; i <= Max; i++) {
        JieC[i] = JieC[i-1] * i % p;
    }    

    LL ans = 1;
    for(i = 0; i < k; i++) {
        ans = ans * C( a[i], b[i] ) % p;
    }
    return ans;
}

int main() {
    int t;
    int i;

    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &p);
        printf("%I64d\n", BigC( n+m, m, p ) );
    }
    return 0;
}

