#include <iostream>
#include <queue>
#include <vector>

using namespace std;

char str[ 1000 ];
char key[ 1000 ][ 200 ];
int n;
char buf[ 1000 ];
int len;
int num[ 1000 ], top;
int flag;

#define ll __int64
#define mod 10007

short hash[ mod + 1 ], cas;
ll Key[ mod + 1 ];
double d[ mod + 1 ][ 200 ];
short d_use[ mod + 1 ][ 200 ];

int val[ 1000 ], F[ 1000 ];
int HH[ 199999 ];
ll po[ 100 ];

int find( char *str ) {
    int i;
    for( i = 0; i < n; i ++ ) {
        if( strcmp( key[i], str ) == 0 )
            return i;
    }
    strcpy( key[n], str );
    return n ++;
}



int HASH( ll va ) {
    int v = va % mod;
    while(1) {
        if( hash[ v ] != cas ) {
            hash[ v ] = cas;
            Key[v] = va;
            return v;
        }else {
            if( Key[v] == va ) {
                return v;
            }
            v ++;
            if( v == mod )
                v = 0;
        }
    }
}

struct point {
    int nex;
    int val;
    int stac;
    ll popo;
    bool friend operator < ( point a, point b ) {
        return a.val > b.val;
    }
}temp, tt;

priority_queue < point > q;

vector < point > vec[ 1000 ];
int C;

int BFS( int u, int v ) {

    int i;
    while( !q.empty() )
        q.pop();

    temp.nex = u;
    temp.popo = po[ val[u] ];
    temp.val = 0;
    temp.stac = HASH( temp.popo );

    q.push( temp );

    while( !q.empty() ) {
        temp = q.top();
        q.pop();

        //printf("%d\n", temp.val );

        if( temp.nex == v && temp.popo == po[C] - 1 )
            return temp.val;

        for( i = vec[temp.nex].size()-1; i >= 0; i-- ) {
            tt.nex = vec[temp.nex][i].nex;
            tt.val = temp.val + vec[temp.nex][i].val;
            if( temp.popo & po[ val[tt.nex] ] ) 
                continue;

            tt.popo = ( temp.popo | po[ val[tt.nex] ] );
            tt.stac = HASH( tt.popo );

            if( d_use[ tt.stac ][ tt.nex ] != cas || tt.val < d[ tt.stac ][ tt.nex ] ) {
                d_use[ tt.stac ][ tt.nex ] = cas;
                d[ tt.stac ][ tt.nex ] = tt.val;
                q.push( tt );
            }
        }
    }
    return -1;
}

int main() {
    int i, j;

    po[0] = 1;
    for( i = 1; i < 100; i ++ )
        po[i] = po[i-1] * (ll) 2;

    scanf("%s", str );
    while( scanf( "%s", str ) != EOF ) {
        n = 0;
        C = 0;
        cas ++;

        for( i = 0; i < 1000; i ++ )
            vec[i].clear();

        while( scanf( "%s", str ) != EOF ) {
            if( strcmp( str, "GRAPH" ) == 0 ) {
                scanf( "%s", str );
                break;
            }
            int u = find( str );
            
            top = 0;
            len = 0;
            flag = 0;
            getchar();
            gets( str );

            double Val;


            for( i = 0; str[i]; i ++) {
                if( str[i] == ' ' ) {
                    if( len ) {
                        buf[ len ] = '\0';
                        if( flag == 0 ) {
                            sscanf( buf, "%d", &val[u] );
                            if( HH[ val[u] ] != cas ) {
                                HH[ val[u] ] = cas;
                                C ++;
                            }
                        }else if( flag == 1 ) {
                            sscanf( buf, "%lf", &Val );
                        }else {
                            num[ top ++ ] = find( buf );
                        }
                        flag ++;
                        len = 0;
                    }
                }else
                    buf[ len ++ ] = str[i];
            }
            
            if( len ) {
                buf[ len ] = '\0';
                if( flag == 0 ) {
                    sscanf( buf, "%d", &val[u] );
                    if( HH[ val[u] ] != cas ) {
                        HH[ val[u] ] = cas;
                        C ++;
                    }
                }else if( flag == 1 ) {
                    sscanf( buf, "%lf", &Val );
                }else {
                    num[ top ++ ] = find( buf );
                }
                flag ++;
                len = 0;
            }

            for( i = 0; i < top; i ++ ) {
                temp.nex = num[i];
                temp.val = Val;
                vec[u].push_back( temp );

                temp.nex = u;
                vec[ num[i] ].push_back( temp );
            }
        }

        for( i = 0; i < n; i ++ ) {
            F[i] = val[i];
        }
        top = 0;
        sort( F, F + n );

        for( i = 1; i < n; i ++ ) {
            if( F[ top ]  != F [i] ) {
                F[ ++top ] = F[i];
            }
        }

        for( i = 0; i < n; i ++ ) {
            for( j = 0; j <= top; j ++ ) {
                if( val[i] == F[j] ) {
                    val[i] = j;
                    break;
                }
            }
        }

        /*for( i = 0; i < n; i ++ ) {
            printf("%s %d\n", key[i], val[i] );
        }
        puts("");*/

        while( scanf( "%s", str ) != EOF ) {
            cas ++;
            if( strcmp( str, "GRAPH" ) == 0 ) {
                break;
            }
            int u = find( str );
            scanf("%s", str );
            int v = find( str );
            double L = BFS( u, v );
            
            printf("%s %s ", key[u], key[v] );
            if( L < 0 )
                printf("NONE\n");
            else
                printf("%.1lf\n", L );
        }
    }
    return 0;
}


/*
GRAPH BEGIN
a 3 1 b e
b 2 2 c
c 1 1 d
d 5
e 2
GRAPH END
a d
a c
GRAPH BEGIN
e 1 2 f
e 1 3 g
f 2
g 2
h 3 4 g f
GRAPH END
h e
*/

