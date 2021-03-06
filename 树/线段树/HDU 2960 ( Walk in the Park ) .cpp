#include <iostream>
#include <algorithm>
using namespace std;

#define INF 100000000

struct Point {
    int x, y;
}Poi[ 100010 ];

int n, m;

struct Elem {
    int Lef;
    int Up, Down;
    int Option;
}A[ 2 ][ 300010 ];
int top[ 2 ];


int hash[ 100010 ];
int tree[ 400101 ];

int cmp( const void *a, const void *b ) {
    Elem *c = ( Elem *)a;
    Elem *d = ( Elem *)b;
    return c->Lef - d->Lef;
}

void Insert( int p, int l, int r, int a, int b, int C ) {
    int mid = ( l + r ) / 2;


    if( l == a && r == b ) {
        if( tree[p] != -1 ) {

            if( C < n ) {
                if( tree[p] >= n && tree[p] != INF ) {
                    hash[ C ] = 1;
                }
            }

            if( C >= n ) {
                if( tree[p] < n && tree[p] != -1 ) {
                    hash[ tree[p] ] = 1;
                }
            }

            tree[p] = C;
            return ;
        }
    }

    if( tree[p] != -1 ) {
        tree[2*p] = tree[p];
        tree[2*p+1] = tree[p];
        tree[p] = -1;
    }

    if( b <= mid ) {
        Insert( 2*p, l, mid, a, b, C );
    }else if( a >= mid + 1 ) {
        Insert( 2*p+1, mid + 1, r, a, b, C );
    }else {
        Insert ( 2*p, l, mid, a, mid, C );
        Insert( 2*p + 1, mid+1, r, mid+1, b, C );

        if( tree[2*p] == tree[2*p+1] && tree[2*p] != -1 ) {
            tree[p] = tree[2*p];
        }
    }
}


int a[ 400010 ], RT;
int O[ 400010 ], Orz;

int Binary( int key ) {
    int low = 1;
    int high = Orz;
    int mid;

    while( low <= high ) {
        mid = ( low + high ) / 2;

        if( key == O[ mid ] ) 
            return mid;
        else if( key > O[ mid ] ) {
            low = mid + 1;
        }else
            high = mid - 1;
    }
}

void Dota( int I ) {
    
    int i;

    RT = 0;
    for(i = 0; i < top[I]; i++) {
        if( A[I][i].Option < n ) {
            a[ RT++ ] = A[I][i].Up;
        }
    }

    sort( a, a + RT );
    Orz = 1;
    O[ Orz++ ] = a[0];

    for(i = 1; i < RT; i++) {
        if( a[i] != a[i-1] ) {
            O[ Orz++ ] = a[i];
        }
    }

    /*for(i = 1; i < Orz; i++) {
        printf("%d ", O[i]);
    }
    puts(")");*/
    Orz --;

    // O[] 保存二分的数组

    for(i = 0; i < top[I]; i++) {
        if( A[I][i].Option >= n ) {
            A[I][i].Up = Orz;
            A[I][i].Down = 1;
        }else {
            A[I][i].Down = A[I][i].Up = Binary(A[I][i].Down);
        }
    }

    qsort( A[I], top[I], sizeof( Elem ), cmp );

    /*for(i = 0; i < top[I]; i++) {
        printf("%d %d %d %d \n", A[I][i].Lef, A[I][i].Up, A[I][i].Down, A[I][i].Option);
    }*/

    for(i = 1; i <= 400000; i++) {
        tree[i] = INF;
    }

    for(i = 0; i < top[I]; i++) {
        Insert( 1, 1, Orz, A[I][i].Down, A[I][i].Up, A[I][i].Option );
    }
}

char str[ 1000 ];

int main() {
    
    int i;

    while( scanf("%d %d", &n, &m) != EOF && ( n||m ) ) {

        top[0] = top[1] = 0;

        for(i = 0; i < n; i++) {

            scanf("%d %d", &Poi[i].x, &Poi[i].y);
            A[ 0 ][ top[0] ].Lef = Poi[i].x;
            A[ 0 ][ top[0] ].Down = A[ 0 ][ top[0] ].Up = Poi[i].y;
            A[ 0 ][ top[0] ].Option = i;
            top[0] ++;

            A[ 1 ][ top[1] ].Lef = Poi[i].y;
            A[ 1 ][ top[1] ].Down = A[ 1 ][ top[1] ].Up = Poi[i].x;
            A[ 1 ][ top[1] ].Option = i;
            top[1] ++;

        }

        for(i = 0; i < m; i++) {
            scanf("%s", str);
            if( str[0] == 'x' ) {
                int num = 0;
                sscanf( &str[2], "%d", &num );

                A[ 0 ][ top[0] ].Lef = num;
                A[ 0 ][ top[0] ].Option = i + n;
                top[0] ++;
            }else {
                int num = 0;
                sscanf( &str[2], "%d", &num );

                A[ 1 ][ top[1] ].Lef = num;
                A[ 1 ][ top[1] ].Option = i + n;
                top[1] ++;
            }
        }    
        memset( hash, 0, sizeof( hash ));

        for(i = 0; i < 2; i++) {
            Dota( i );
        }

        int coun = 0;
        for(i = 0; i < n; i++) {
            if( hash[i] )
                coun ++;
        }

        printf("%d\n", coun );

    }
    return 0;
}

