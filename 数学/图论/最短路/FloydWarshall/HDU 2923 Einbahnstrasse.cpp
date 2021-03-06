#include <iostream>
#include <string>
#include <map>

using namespace std;

int n, c, m;
int start;
char str[ 1000 ], ma[ 1000 ], pre[ 1000 ];
map < string, int > Map;
int T;
string buf;
int p, num;

int stack[ 10000 ];
int C[200][200];
int top;

int main() {

    int u, v;
    int t = 1;
    int i, j, k;

    while( scanf("%d %d %d", &n, &c, &m) != EOF ) {

        if( !n && !c && !m )
            break;

        Map.clear();
        top = 0;

        for(i = 0; i < 200; i++) {
            for(j = 0; j < 200; j++) {
                if( i == j )
                    C[i][j] = 0;
                else
                    C[i][j] = 100000000;
            }
        }

        T = 1;
        scanf("%s", str);

        buf = str;
        u = Map[ buf ];
        
        if( !u ) {
            u = Map[ buf ] = T ++;
        }
        start = u;

        for(i = 1; i <= c; i++) {
            scanf("%s", str);
            buf = str;
            u = Map[ buf ];

            if( !u ) {
                u = Map[ buf ] = T++;
            }
            stack[ top++ ] = u;
        }

        while( m-- ) {

            scanf("%s %s %s", str, ma, pre);
            buf = str;
            u = Map[ buf ];

            if( !u ) {
                u = Map[ buf ] = T++;
            }

            buf = pre;
            v = Map[ buf ];
            if( !v ) {
                v = Map[ buf ] = T++;
            }

            int len = strlen ( ma );

            p = 0;
            while( !( ma[p] >= '0' && ma[p] <= '9' ) )
                p ++;
            sscanf(&ma[p], "%d", &num );

            if( ma[0] == '<' ) {
                if( num < C[v][u] )
                    C[v][u] = num;
            }

            if( ma[ len-1 ] == '>' ) {
                if( num < C[u][v] )
                    C[u][v] = num;
            }
        }

        for(k = 1;k < T; k++) {
            for(i = 1; i < T; i++) {
                for(j = 1; j < T; j++) {

                    if( C[i][k] != 100000000 && C[k][j] != 100000000 ) {
                        if( C[i][k] + C[k][j] < C[i][j] )
                            C[i][j] = C[i][k] + C[k][j];
                    }
                }
            }
        }

        int sum = 0;
        for(i = 0; i < top; i++) {
            sum += C[ start ][ stack[i] ] + C[ stack[i] ][ start ];
        }

        printf("%d. %d\n", t++, sum);

    }

    return 0;
}
