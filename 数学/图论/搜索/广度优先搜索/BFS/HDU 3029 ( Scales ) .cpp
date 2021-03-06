#include <iostream>
#include <algorithm>
using namespace std;

#define LL long long

LL f[ 30 ];
int n;
LL all[ 30 ];
int stack[ 1000 ], top;
int st;
int lef[30], rig[30], lt, rt;

int dfs( int depth, LL sum ) {
    int i;



    if( sum == n ) {
        st = depth;
        return 1;
    }

    if( depth == -1 )
        return 0;

    for(i = -1; i <= 1; i++) {
        stack[ depth ] = i;

        if( sum + all[depth] < n )
            return 0;
        if( sum - all[depth] > n )
            return 0;

        if( dfs( depth-1, sum + (LL)i * f[depth] ) ) 
            return 1;
    }
    return 0;
}

int main() {
    int i, j;
    f[0] = 1;
    for(i = 1; i < 22; i++) {
        f[i] = f[i-1] * 3;
        //printf("%I64d\n", f[i]);
    }
    all[0] = 1;
    for(j = 1; j < 22; j++) {
        all[j] = all[j-1] + f[j];
        //printf("%I64d\n", all[j]);
    }


    while( scanf("%d", &n) != EOF ) {
        dfs( 20, 0 );
        lt = rt = 0;

        for( i = st + 1; i < 21; i++) {
            if( stack[i] == 1 ) {
                lef[ lt ++ ] = i;
            }
            if( stack[i] == -1 ) {
                rig[ rt ++ ] = i;
            }
        }

        sort( lef, lef + lt );
        sort( rig, rig + rt );



        printf("%d", rt );
        for(i = 0; i < rt; i++) {
            printf(" %lld", f[ rig[i] ]);
        }
        puts("");
        
        printf("%d", lt );
        for(i = 0; i < lt; i++) {
            printf(" %lld", f[ lef[i] ] );
        }
        puts("");
    }
}

