#include <iostream>

using namespace std;

#define ll __int64

ll f[ 100 ], A[ 10000 ], a[ 1000 ], T, pre;
int C, id;
int top;
int n;

int main() {
    int t;
    int i, j;
    int C;

    f[0] = 1;
    f[1] = 1;
    for( i = 2; i < 20; i ++ )
        f[i] = f[i-1] + f[i-2];

    scanf("%d", &t );
    while( t-- ) {
        scanf("%d", &n );
        for( i = 0; i < n; i ++ ) {
            scanf("%I64d", &a[i] );
        }
        for( i = 0; i <= 8; i ++ ) {
            A[0] = a[0];
            if( i == 0 ) {
                A[1] = a[1];
            }else {
                if( (a[1] - f[i-1] * a[0]) % f[i] == 0 ) {
                    A[1] = (a[1] - f[i-1] * a[0]) / f[i];
                }else
                    continue;
            }
            //printf("%d %I64d\n", i , A[1] );

            top = 1;
            id = 1;
            C = 0;
            while( id < n && C < 8 ) {
                if( A[top] == a[id] ) {
                    C = 0;
                    id ++;
                }
                C ++;
                ++top;
                A[top] = A[top-1] + A[top-2];
            }

            if( id == n )
                break;
        }



        if( i <= 8 ) {    
            for( i = top; i < 10; i ++ )
                A[i] = A[i-1] + A[i-2];
            printf("STABLE");
            for( i = 0; i < 5; i ++ )
                printf(" %I64d", A[i] );
            puts("");
        }else {
            printf("UNSTABLE\n");
        }
    }
    return 0;
}

