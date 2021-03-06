#include <iostream>

using namespace std;

int dfs( int n ) {
    if( n == 1 || n == 2 )
        return 0;
    if( n % 2 == 0 )
        return 2 * dfs( n/2 );
    return dfs( n/2+1 ) + dfs( n/2 ) + 1;
}

int main() {
    int t;
    int n;
    scanf("%d", &t );

    while( t-- ) {
        scanf("%d", &n );
        printf("%d\n", dfs(n) );
    }
    return 0;
}

