#include <iostream>
#include <queue>
using namespace std;

#define mod 30007

int hash[ mod + 1 ];
char key[ mod + 1 ][ 102 ];
int F[ mod + 1 ];

struct point {
    int state;
    int step;
    int pos;
}temp, tt;

int len;
int cas = 0;


int HASH( char* str ) {
    int i;
    int S = 0;
    for( i = 0; i < len; i ++ ) {
        S = (S * 3 + (int)str[i] ) % mod;
    }

    while(1) {
        if( hash[S] != cas ) {
            hash[S] = cas;
            for( i = 0; i < len; i ++ ) {
                key[S][i] = str[i];
            }
            return S;
        }else {
            for( i = 0; i < len; i ++ ) {
                if( key[S][i] != str[i] )
                    break;
            }
            if( i == len )
                return S;
            S ++;
            if( S == mod )
                S = 0;
        }
    }
}

char str[ 1000 ];
queue < point > q;


bool YES( int idx ) {
    int i, j;

    /*for( i = 0; i < len; i ++ ) {
        printf("%d", key[idx][i]);
    }
    puts("");*/

    for( i = 0; i < len; i ++ ) {
        if( key[idx][i] == 1 ) {
            for( j = i-1; j >= 0; j -- ) {
                if( key[idx][j] == 0 )
                    break;
            }
            if( j >= 0 ) {
                for( j = i+1; j < len; j ++ ) {
                    if( key[idx][j] == 0 )
                        return false;
                }
            }
        }
    }
    return true;
}

int main() {
    
    int i, j;
    while( scanf( "%s", str ) != EOF ) {
        
        if( str[0] == '-' )
            break;

        cas ++;
        len = strlen( str );
        for( i = 0; i < len; i++ ) {
            if( str[i] == 'B' )
                str[i] = 0;
            if( str[i] == 'W' )
                str[i] = 1;
            if( str[i] == 'F' ) {
                str[i] = 2;
                temp.pos = i;
                temp.step = 0;
            }
        }

        while( !q.empty() )
            q.pop();


        temp.state = HASH( str );
        F[ temp.state ] = cas;

        q.push( temp );
        int flag = -1;

        while( !q.empty() ) {
            temp = q.front();
            q.pop();

            if( temp.step == 10 )
                continue;
            
            if( YES( temp.state ) ) {
                flag = temp.step;
                break;
            }

            for( i = -1; i <= 1; i += 2 ) {
                tt.pos = temp.pos + i;
                tt.step = temp.step + 1;

                if( tt.pos < 0 || tt.pos >= len )
                    continue;
                for( j = 0; j < len; j ++ )
                    str[j] = key[temp.state][j];
                char c = str[ tt.pos ];
                str[ tt.pos ] = str[ temp.pos ];
                str[ temp.pos ] = c;
                tt.state = HASH( str );
                if( F[ tt.state ] != cas ) {
                    F[ tt.state ] = cas;
                    q.push( tt );
                }


                tt.pos = temp.pos + 2*i;
                tt.step = temp.step + 1;

                if( tt.pos < 0 || tt.pos >= len )
                    continue;
                for( j = 0; j < len; j ++ )
                    str[j] = key[temp.state][j];
                c = str[ tt.pos ];
                str[ tt.pos ] = str[ temp.pos ];
                str[ temp.pos ] = c;
                str[ temp.pos ] ^= 1;

                tt.state = HASH( str );
                if( F[ tt.state ] != cas ) {
                    F[ tt.state ] = cas;
                    q.push( tt );
                }
            }
        }

        printf("%d. %d\n", cas, flag );
    }
    return 0;
}

