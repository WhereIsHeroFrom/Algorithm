#include <iostream>

using namespace std;

bool f[ 1000 ];
__int64 n;
__int64 Prime[ 100 ], size;
__int64 Jin[ 100 ], all;
int stack[ 100 ], top;

struct point {
    int Pos;
    int Val;
}p[ 1000 ];
int X;


int main() {
    int i, j;

    f[0] = f[1] = 1;

    for(i = 2; i <= 100; i ++ ) {
        if( !f[i] ) {
            Prime[ size++ ] = i;
            for(j = i+i; j <= 100; j += i ) {
                f[j] = 1;
            }
        }
    }

    Jin[0] = 2;
    for(i = 1; i < size; i++) {
        Jin[i] = Jin[i-1] * Prime[i];
        if( Jin[i] > ( __int64 )4294967296 )
            break;
    }
    all = i;

    while( scanf( "%I64d", &n ) != EOF && n ) {
        top = 0;
        __int64 N = n;

        if( n == 1 ) {
            printf("1 = 1\n");
            continue;
        }else {
            for(i = all - 1 ; i >= 0; i-- ) {
                if( n / Jin[i] )
                    break;
            }
            int first = i;
            int RT = first;

            while( n != 1 && n ) {
                stack[ top++ ] = n / Jin[ first ];
                n -= (n / Jin[ first ]) * Jin[ first ];
                first --;
            }

            X = 0;

            if( n == 1 ) {
                p[ X ].Pos = -1;
                p[ X ].Val = 1;
                X ++;
            }

            for(i = top - 1 ; i >= 0 ; i-- ) {
                if( stack[i] ) {
                    p[ X ].Pos = RT - i;
                    p[ X ].Val = stack[i];
                    X ++;
                }
            }

            printf("%I64d = ", N);

            if( p[ 0 ].Pos == -1 )
                printf("1");
            else {
                printf("%d", p[ 0 ].Val);
                for(i = 0; i <= p[ 0 ].Pos; i++) {
                    printf("*%I64d", Prime[i]);
                }
            }

            for( i = 1; i < X; i++) {
                printf(" + %d", p[i].Val);
                for(j = 0; j <= p[i].Pos; j++) {
                    printf("*%I64d", Prime[j]);
                }
            }
            puts("");
        }
    }
    return 0;
}
