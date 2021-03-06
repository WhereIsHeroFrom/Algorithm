#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector < int > vec[ 100010 ];
int in[ 100010 ];
int hash[ 100010 ];
int Count, D[ 100010 ] ;

void dfs( int key ) {
    if( hash[ key ] != -1 )
        return ;
    hash[ key ] = Count;
    for( int i = vec[key].size() - 1; i >= 0; i-- ) {
        dfs( vec[key][i] );
    }
}

int main() {
    int x, y;
    int i;
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        memset( hash, -1, sizeof( hash ) );
        memset( D, 0, sizeof( D ));
        memset( in, 0, sizeof( in ) );
        for( i = 1; i <= n; i ++ )
            vec[i].clear();
        for( i = 0; i < m; i ++ ) {
            scanf("%d %d", &x, &y );
            in[x]++;
            in[y]++;
            vec[x].push_back(y);
            vec[y].push_back(x);
        }

        Count = 0;
        for( i = 1; i <= n; i ++ ) {
            if( in[i] == 0 )
                continue;
            if( hash[i] == -1 ) {
                dfs(i);
                Count ++;
            }
        }

        for( i = 1; i <= n; i ++ ) {
            if( in[i] & 1 )
                D[ hash[i] ] ++;
        }

        int Sum = 0;
        for( i = 0; i < Count; i++ ) {
            Sum += D[i] / 2;
            if( D[i] == 0 )
                Sum ++;
        }
        printf("%d\n", Sum );
    }
    return 0;
}


