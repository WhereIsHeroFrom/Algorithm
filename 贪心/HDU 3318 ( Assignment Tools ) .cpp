#include <iostream>
#include <vector>
using namespace std;

int n, m;
int need[101][101];
int lott[101][101];
int now[101];


vector < int > vec, buf;

int main() {
    int i, j;
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        for(i = 1; i <= n;  i ++ ) {
            scanf("%d", &now[i] );
        }

        for( i = 1; i <= m; i ++ ) {
            for( j = 1; j <= n; j ++ )
                scanf("%d", &need[i][j] );
        }
        for( i = 1; i <= m; i ++ ) {
            for( j = 1; j <= n; j ++ ) {
                scanf("%d", &lott[i][j] );
                now[j] -= lott[i][j];
            }
        }

        vec.clear();
        for( i = 1; i <= m; i ++ ) {
            vec.push_back(i);
        }

        while( true ) {
            buf.clear();
            for( i = vec.size()-1; i >= 0; i-- ) {
                int    N = vec[i];
                for( j = 1; j <= n; j ++ ) {
                    if( now[j] < need[N][j] - lott[N][j] )
                        break;
                }

                if( j <= n ) {
                    buf.push_back(N);
                }else {
                    for( j = 1; j <= n; j ++ ) {
                        now[j] += lott[N][j];
                    }
                }
            }
            if( buf.size() == vec.size() )
                break;
            vec = buf;
        }

        if( vec.size() )
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
