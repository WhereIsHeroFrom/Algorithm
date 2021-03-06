#include <iostream>

using namespace std;

#define Mod 3000007

bool hash[ Mod + 1 ];
int key[ Mod + 1 ];

int HASH( int S ) {
    int v = S % Mod;
    while( 1 ) {
        if( hash[ v ] ) {
            if( key[ v ] == S )
                return v;
            else {
                v ++;
                if( v == Mod )
                    v = 0;
            }
        }else {
            hash[ v ] = 1;
            key[ v ] = S;
            return v;
        }
    }
}

int H[ Mod + 1 ];

struct point {
    int num;
    int S;
    int pre;
    int flag;
}q[ 1000000 ], temp, tt;

int front, rear;
int ID;
int n, m;
int stack[ 1000 ], top;

int main() {

    int i;
    int t;

    memset( H, -1, sizeof( H ));
    front = rear = 0;
    n = 10000;
    m = 10000;
    temp.flag = 0;
    temp.pre = -1;
    temp.S = 0;
    ID = HASH( temp.S );
    H[ ID ] = 0;

    q[ rear ++ ] = temp;


    while( front < rear ) {
        temp = q[ front ++ ];
        tt.pre = front - 1;

        for(i = 0; i <= 9; i++) {

            if( i == 0 && !temp.flag )
                continue;

            tt.flag = temp.flag + 1;
            tt.num = i;
            int a = ( temp.S/20000 + i );
            int b = ( temp.S%20000 + i*i );

            if( a <= n && b <= m ) {
                tt.S = a * 20000 + b;
                ID = HASH( tt.S );
                if( H[ ID ] == -1 ) {

                    if( tt.flag <= 100 ) {
                        H[ ID ] = rear;
                        q[ rear ++ ] = tt;
                    }
                }
            }
        }
    }


    scanf("%d", &t);
    while( t-- ) {
        scanf("%d %d", &n, &m);
        int ID = HASH( n * 20000 + m );

        if( H[ ID ] == -1 )
            printf("No solution\n");
        else {
            temp = q[ H[ ID ] ];
            top = 0;
            while( temp.pre != -1 ) {
                stack[ top++ ] = temp.num;
                temp = q[ temp.pre ];
            }

            for(i = top-1; i >= 0; i--)
                printf("%d", stack[i]);
            puts("");
        }
    }
    return 0;
}

