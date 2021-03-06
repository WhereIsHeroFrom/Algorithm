#include <iostream>

using namespace std;

struct point {
    int h;
    int m;
    int s;
}p[ 50000 ], temp, buf[ 10 ][ 50000 ];
int al[10];
int top;
int hash[ 60 ][ 60 ][ 60 ];
int n;
int RT[ 60 ][ 60 ][ 60 ];
point ea[ 50000 ];
int tttt;

void process( int key, point temp ) {

    int i;

    // 初始化
    memset( hash, 0, sizeof( hash ) );
    al[ key ] = 0;
    tttt = 0;

    // 3的全排列
    buf[ key ][ al[ key ] ].h = temp.h; 
    buf[ key ][ al[ key ] ].m = temp.m;
    buf[ key ][ al[ key ] ].s = temp.s;    
    point a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    buf[ key ][ al[ key ] ].h = temp.h; 
    buf[ key ][ al[ key ] ].m = temp.s;
    buf[ key ][ al[ key ] ].s = temp.m;     
    a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    buf[ key ][ al[ key ] ].h = temp.m; 
    buf[ key ][ al[ key ] ].m = temp.h;
    buf[ key ][ al[ key ] ].s = temp.s;    
    a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    buf[ key ][ al[ key ] ].h = temp.m; 
    buf[ key ][ al[ key ] ].m = temp.s;
    buf[ key ][ al[ key ] ].s = temp.h;    
    a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    buf[ key ][ al[ key ] ].h = temp.s; 
    buf[ key ][ al[ key ] ].m = temp.m;
    buf[ key ][ al[ key ] ].s = temp.h;    
    a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    buf[ key ][ al[ key ] ].h = temp.s; 
    buf[ key ][ al[ key ] ].m = temp.h;
    buf[ key ][ al[ key ] ].s = temp.m;    
    a = buf[ key ][ al[ key ] ];
    ea[ tttt++ ] = a;

    for(i = 0; i < tttt; i++) {

        ea[i].h %= 60;
        ea[i].m %= 60;
        ea[i].s %= 60;
        point a = ea[i];

        while( 1 ) {
            if( hash[ a.h ][ a.m ][ a.s ] )
                break;

            if( RT[ a.h ][ a.m ][ a.s ] ) {
                buf[ key ][ al[ key ] ++ ] = a;
            }

            hash[ a.h ][ a.m ][ a.s ] = 1;    
            a.h = (a.h + 1 ) % 60;
            a.m = (a.m + 1 ) % 60;
            a.s = (a.s + 1 ) % 60;
        }
    }


    for(i = 0; i < al[ key ]; i++) {
        p[ top ++ ] = buf[ key ][ i ];
    }
}

int cmp( const void *a, const void *b ) {
    point *c = ( point *)a;
    point *d = ( point *)b;
    if( c->h != d->h )
        return c->h - d->h;
    if( c->m != d->m )
        return c->m - d->m;
    return c->s - d->s;
}

int Fit( int key ) {

    int i, j, k;

    for(i = 0; i < top; i++) {
        int pre = p[i].h  / 5 * 3600 + p[i].m * 60 + p[i].s;

        for(j = 0; j < n; j++) {
            for(k = 0; k < al[ j ]; k++) {
                int Tim = buf[j][k].h / 5 * 3600 + buf[j][k].m * 60 + buf[j][k].s;

                if( pre + key >= Tim && Tim >= pre ) 
                    break;
            }

            if( k == al[ j ] )    
                break;
        }
        if( j == n )
            return p[i].h / 5 * 3600 + p[i].m * 60 + p[i].s;
    }
    return -1000000;
}

int main() {

    int i, j, k;

    for(i = 0; i < 12 * 60 * 60; i++) {
        RT[ i/720 ][ (i%3600) / 60 ][ i % 60 ] = 1;
    }

    while( scanf("%d", &n) != EOF && n) {
        top = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &temp.h, &temp.m, &temp.s);
            process( i, temp );
        }

        /*for(i = 0; i < al[ 0 ]; i ++) {
            printf("%d %d %d\n", buf[0][i].h, buf[0][i].m, buf[0][i].s);
        }*/

        qsort( p, top, sizeof( point ), cmp );

        /*for(i = 0; i < top; i++) {
            printf("%d:%d:%d\n", p[i].h, p[i].m, p[i].s);
        }*/

        /*for(i = 0; i < n; i++) {
            printf("%d\n", al[i]);
        }*/

        int low, high, mid;

        low = 0;
        high = 10000000;
    
        while( low < high ) {
            mid = ( low + high ) / 2;  //
            if( Fit( mid ) != -1000000 ) {
                high = mid - 1;
            }else
                low = mid + 1;
        }

        int op = mid - 5;
        if( op < 0 )
            op = 0;


        int buf;
        for(i = op; i < op + 10; i++) {
            buf = Fit( i );
            if( buf != -1000000 )
                break;
        }

        printf("%02d:%02d:%02d ", buf / 3600 % 12, buf / 60 % 60, buf % 60 );
        buf += i;
        printf("%02d:%02d:%02d\n", buf / 3600 % 12, buf / 60 % 60, buf % 60 );
    }
    return 0;
}
