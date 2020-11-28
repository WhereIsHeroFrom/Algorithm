#include <iostream>

using namespace std;

#define ll __int64
ll n;
ll s, e, L, quan, T;

int main() {

    while( scanf("%I64d", &n) != EOF ) {
        if( n == 1 ) {
            printf("1 0\n");
            continue;
        }
        L = 1;
        s = 2;
        e = 4;
        quan = 3;
        T = 1;

        while ( 1 ) {
            if( n >= s && n <= e ) {
                break;
            }
            quan *= 3;
            s = e + 1;
            e = s + quan - 1;
            T *= 2;
            L += T;
        }
        printf("%I64d %I64d\n", n, L );
    }
}
