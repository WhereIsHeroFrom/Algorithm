#include <iostream>

using namespace std;

#define ll __int64

ll n;

ll exp( ll a, ll b, ll c ) {
    if( b == 0 )
        return 1 % c;
    ll tmp = exp( (a*a)%c, b/2, c );
    if( b & 1 )
        tmp = tmp * a % c;
    return tmp;
}

int main() {
    while( scanf( "%I64d", &n ) != EOF && n ) {
        printf("%I64d\n", (exp( 2, n-1, n ) + 1 ) % n );
    }
    return 0;
}


