#include <iostream>

using namespace std;

int id( char *str ) {
    if( strcmp( str, "COOL" ) == 0 )
        return 0;
    if( strcmp( str, "GOOD" ) == 0 )
        return 1;
    return 2;
}

int c = 0, g = 0, m = 0;
int MAX = 0;
char str[ 10 ];
int p;

void ProMAX(int u) {
    p += u * (MAX/20);
}

int main() {
    int t;
    int i, j;
    int n;

    scanf("%d", &t);

    while( t-- ) {
        scanf("%d", &n );


        p = 0;
        c = g = 0;
        for( i = 0; i < n; i ++ ) {
            scanf("%s", str );
            if( id( str ) == 0 ) {
                c ++;
                ProMAX(10);
                MAX += 2;
            }else if( id( str ) == 1 ) {
                g ++;
                ProMAX(5);
                MAX += 1;
            }else {
                MAX = 0;
            }
        }
        printf("%d\n", p + c * 100 + g * 50 );
    }
    return 0;
}

