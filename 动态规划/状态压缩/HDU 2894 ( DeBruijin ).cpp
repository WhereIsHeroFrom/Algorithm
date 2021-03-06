#include <iostream>

using namespace std;

int k;
int stack[ 10000 ], top;
int hash[ 10000 ];

int dfs( int depth, int pre ) {
    int i;

    if( depth == (1<<k) ) {
        for(i = 0; i < k - 1; i++) {
            if( pre & ( 1 << (k-1) ) )
                pre = ( pre ^ ( 1<<(k-1) ) );
            pre <<= 1;

            if( hash[ pre ] )
                return 0;
        }

        for(i = 0; i < (1<<k); i++)
            printf("%d", stack[i]);
        puts("");
        return 1;
    }

    for(i = 0; i < 2; i++) {
        stack[ depth ] = i;
        int nex = pre;
        
        if( pre & ( 1 << (k-1) ) )
            nex = ( pre ^ ( 1<<(k-1) ) );

        nex <<= 1;
        nex += i;

        if( !hash[ nex ] ) {
            hash[ nex ] = 1;
            if( dfs( depth+1, nex ) )
                return 1;
            hash[ nex ] = 0;
        }
    }
    return 0;
}

int main() {
    int i;
    while( scanf("%d", &k) != EOF ) {
        printf("%d ", (1<<k) );
        memset( hash, 0, sizeof( hash ));
        top = 0;
        for(i = 0; i < k; i++)
            stack[ top++ ] = 0;
        hash[0] = 1;
        dfs( top, 0 );
    }
    return 0;
}
