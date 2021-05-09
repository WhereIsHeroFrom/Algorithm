#include<bitset>
using namespace std;

#define maxn 10000010
bitset< maxn > f;
int R[ 10000010 ];

__int64 Bin( __int64 a, __int64 b, __int64 c ) {
    if( b == 0 ) {
        return 1 % c;
    }
    __int64 x = Bin( (a*a) % c, b/2, c );
    if( b & 1 ) 
        x = ( x * a ) % c;
    return x;
}
int n;
__int64 M;

int main() {

    int t;
    int i, j;

    for(i = 2; i <= 10000000; i++) {
        if( !f[i] ) {
            R[i] = 1;
            for(j = i+i; j <= 10000000; j += i ) {
                f[j] = 1;
                R[j] ++;
            }
        }
        R[i] += R[i-1];
    }

    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %I64d", &n, &M);
        printf("%I64d\n", Bin( 2, R[n], M ) );
    }
    return 0;
}

