#include <iostream>
#include <queue>
using namespace std;

struct point {
    int circle[2];
    int state;
    int step;
}temp[2], tt[2];

queue < point > q[2];
int hash[2][800000];
int key[2][800000];

int HASH( int mode, int mod, int val, int step ) {
    int rt = val % 799997;

    while( 1 ) {

        if( hash[ mod ][ rt ] == -1 ) {

            if( mode ) {
                return -1;
            }
            hash[ mod ][ rt ] = step;
            key[ mod ][ rt ] = val;
            return rt;
        }else {
            if( key[ mod ][ rt ] == val ) {
                if( mode )
                    return hash[ mod ][ rt ];
                return -1;
            }else {
                rt += 3;
                if( rt >= 799997 )
                    rt %= 799997;
            }
        }
    }
}

char str[ 30 ];
int ans;

int State( int sta, char *str ) {
    int i, j;
    int sum = 0;
    for(i = sta; i < sta + 13; i++) {
        if( str[i] == 'y')
            sum = sum * 2 + 1;
        else
            sum = sum * 2;
    }
    return sum;
}

int ClockWise ( int key ) {
    int rt = ( key & 1 );
    key >>= 1;
    rt <<= 12;
    return rt + key;
}

int AC( int a, int b ) {
    int i;
    int Mina = a, Minb = b;

    for(i = 0; i < 12; i++) {
        a = ClockWise( a );    
        if( a < Mina )
            Mina = a;
        
        b = ClockWise( b );    
        if( b < Minb )
            Minb = b;
    }
    return ( Mina << 13 ) + Minb;
}

int main() {

    int i, j, k;
    while( scanf( "%s", str ) != EOF ) {

        memset( hash, -1, sizeof( hash ));
        for(i = 0; i < 2; i++) {
        
            while( !q[i].empty() ) {
                q[i].pop();
            }
            temp[i].circle[0] = State( 0, str );
            temp[i].circle[1] = State( 13, str );
            temp[i].state = AC( temp[i].circle[0], temp[i].circle[1] );
            temp[i].step = 0;
            q[ i ].push( temp[i] );
            HASH( 0, i, temp[i].state, 0 );
            strcpy( str, "gggggggggggggyyyyyyyyyyyyy" );
        }

        int mod = 1;
        ans = -1;

        int t = 0;

        while( !q[0].empty() || !q[1].empty() ) {
            while( !q[ mod ].empty() ) {

                temp[ mod ] = q[ mod ].front();
                q[ mod ].pop();

                int u = HASH( 1, 1-mod, temp[ mod ].state, 0 );

                if( u != -1 ) {
                    ans = u + temp[ mod ].step;
                    break;
                }
                
                int up = temp[ mod ].circle[0];

                for(i = 0; i < 13; i++) {
                    int down = temp[ mod ].circle[1];
                    for(j = 0; j < 13; j++) {

                        tt[ mod ].circle[0] = ( up ^ ( up & 7 ) ) + ( down & 7 );
                        tt[ mod ].circle[1] = ( down ^ ( down & 7 ) ) + ( up & 7 );
                        tt[ mod ].state = AC( tt[ mod ].circle[0], tt[ mod ].circle[1]);
                        tt[ mod ].step = temp[ mod ].step + 1;

                        int buf = HASH( 0, mod, tt[ mod ].state, tt[ mod ].step );
                        if( buf != -1 ) {

                            int u = HASH( 1, 1-mod, tt[ mod ].state, 0 );
                            if( u != -1 ) {
                                ans = u + tt[ mod ].step;
                                break;
                            }

                            q[ mod ].push( tt[ mod ] );
                        }

                        int ty = ClockWise( down );

                        while( j < 13 && ty == down ) {
                            down = ty;
                            ty = ClockWise( down );
                            j ++;
                        }
                        down = ty;
                    }        

                    if( ans != -1 )
                        break;

                    int rt = ClockWise( up );
                    while( i < 13 && rt == up ) {
                        up = rt;
                        rt = ClockWise( up );
                        i ++;
                    }
                    up = rt;
                }

                if( ans != -1 )
                    break;

                if( !q[ mod ].empty() ) {
                    if( q[ mod ].front().step != temp[ mod ].step )
                        break;
                }
            }

            if( ans != -1 )
                break;
            mod ^= 1;
        }

        printf("%d\n", ans);
    }
    return 0;
}
