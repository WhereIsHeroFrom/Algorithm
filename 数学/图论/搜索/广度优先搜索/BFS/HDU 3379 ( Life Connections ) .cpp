#include <iostream>
#include <queue>
using namespace std;

char str[ 1000 ];
char key[ 1000 ][ 200 ];
int n;
char buf[ 1000 ];
int len;
int num[ 1000 ], top;


int find( char *str ) {
    int i;
    for( i = 0; i < n; i ++ ) {
        if( strcmp( key[i], str ) == 0 )
            return i;
    }
    strcpy( key[n], str );
    return n ++;
}

int map[ 1000 ][ 1000 ];
int dis[ 1000 ], pat[ 1000 ];

struct point {
    int nex;
    int val;
    bool friend operator < ( point a, point b ) {
        return a.val > b.val;
    }
}temp, tt;

priority_queue < point > q;

int BFS( int u, int v ) {

    int i;

    if( u == v )
        return map[u][v];

    while( !q.empty() )
        q.pop();
    temp.nex = u;
    temp.val = 0;
    memset( dis, -1, sizeof( dis ) );
    pat[u] = 1;

    q.push( temp );

    while( !q.empty() ) {
        temp = q.top();
        q.pop();

        for( i = 0; i < n; i ++ ) {
            if( map[temp.nex][i] ) {
                tt.nex = i;
                tt.val = temp.val + 1;
                if( dis[ tt.nex ] == -1 || tt.val < dis[ tt.nex ] ) {
                    dis[ tt.nex ] = tt.val;
                    pat[ tt.nex ] = pat[ temp.nex ];
                    q.push( tt );
                }else if( tt.val == dis[ tt.nex ] )
                    pat[ tt.nex ] += pat[ temp.nex ];
            }
        }
    }
    return pat[ v ];
}

int main() {
    int i;
    scanf("%s", str );
    while( scanf( "%s", str ) != EOF ) {
        
        n = 0;
        memset( map, 0, sizeof( map ) );

        while( scanf( "%s", str ) != EOF ) {
            if( strcmp( str, "GRAPH" ) == 0 ) {
                scanf( "%s", str );
                break;
            }
            int u = find( str );
            getchar();
            gets( str );

            top = 0;
            for( i = 0; str[i]; i ++ ) {
                if( str[i] == ' ' ) {
                    if( len ) {
                        buf[ len ] = '\0';
                        num[ top ++ ] = find( buf );
                        len = 0;
                    }
                }else
                    buf[ len++ ] = str[i];
            }
            if( len ) {
                buf[ len ] = '\0';
                num[ top ++ ] = find( buf );
                len = 0;
            }

            for( i = 0; i < top; i ++ ) {
                map[ u ][ num[i] ] = 1;
                map[ num[i] ][ u ] = 1;
            }
        }

        while( scanf( "%s", str ) != EOF ) {
            if( strcmp( str, "GRAPH" ) == 0 ) {
                break;
            }
            int u = find( str );
            scanf("%s", str );
            int v = find( str );
            printf("%s %s %d\n", key[u], key[v], BFS( u, v ) );
        }
    }
    return 0;
}


