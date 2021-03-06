#include <iostream>

using namespace std;

int f[ 100 ];
int small[ 2600 ][ 2600 ];
int Max( int a, int b ) { return a > b ? a : b; }
int Min( int a, int b ) { return a < b ? a : b; }

int dp ( int x, int y ) {

    int i;
    int st, en, sum = 0;

    if( x < 2600 && y < 2600 ) {
        if( small[ x ][ y ] != -1 )
            return small[ x ][ y ];
    }

    if( x == y ) {
        if( y == 0 )
            return 0;
        y = 0;
        while( x ) {
            if( x & 1 )
                y ++;
            x >>= 1;
        }
        return y;
    }

    if( x == 0 ) {
        x ++;
    }

    int len = 0, ty = x;

    while( ty ) {
        ty >>= 1;
        len ++;
    }

    for(i = len - 1; i < 24; i++) {
        st = f[i];
        if( x > st )
            st = x;
        en = f[i+1]-1;
        if( y < en )
            en = y;

        if( st <= en ) {
            int buf = dp( st - f[i], en - f[i]);
            if( st - f[i] < 2600 && en - f[i] < 2600 )
                small[ st - f[i] ][ en - f[i] ] = buf;
            sum += ( en - st + 1 ) + buf;
        }

        if( y == en )
            return sum;

        if( f[i] > y )
            return sum;
    }
    return sum;
}

int main() {
    int i, a, b;
    f[0] = 1;
    for(i = 1; i <= 30; i++)
        f[i] = f[i-1] * 2;
    double sum = 0;
    int st, en;
    memset( small, -1, sizeof( small ));
    while( scanf("%d %d", &a, &b) != EOF ) {
        sum = 0;
        for(i = 0; i < 24; i++) {
            st = Max( f[i], a );
            en = Min( f[i+1]-1, b );
            if( st <= en ) {
                //printf("%d %d\n", st, en);
                sum += dp( st, en ) / (i + 1.0);
            }
        }
        printf("%.6lf\n", sum / (b - a + 1) );
    }
}

/*
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
1 10000000
*/
