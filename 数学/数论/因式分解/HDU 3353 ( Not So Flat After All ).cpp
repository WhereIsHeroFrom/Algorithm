#include <iostream>
#include <vector>

using namespace std;

#define maxn 1000000

bool f[ maxn ];
int H[ maxn ];
int prime[ maxn ], size;
int zty[ 1000 ];

void Init() {
    int i, j;
    f[0] = f[1] = 1;
    for( i = 2; i < maxn; i ++ ) {
        if( !f[i] ) {
            prime[ size++ ] = i;
            for( j = i+i; j < maxn; j += i ) {
                f[j] = 1;
            }
        }
    }
}

int ABS( int a ) {
    return a < 0 ? -a : a;
}

struct point {
    int k;
    int num[ 100 ];
    int pri[ 100 ];
};

point Cal( int key ) {
    int i;
    point tmp;
    tmp.k = 0;
    if( !key ) {
        return tmp;
    }
    for( i = 0; i < size; i ++ ) {
        if( key % prime[i] == 0 ) {
            tmp.num[ tmp.k ] = 0;
            tmp.pri[ tmp.k ] = prime[i];
            while( key % prime[i] == 0 ) {
                key /= prime[i];
                tmp.num[ tmp.k ] ++;
            }
            tmp.k ++;
        }
    }
    return tmp;
}

int main() {
    Init();
    int a, b;
    int i, j;
    int cas = 0;

    while( scanf( "%d %d", &a, &b ) != EOF && (a||b) ) {
        point A, B;
        A = Cal(a);
        B = Cal(b);
        cas ++;

        int L = A.k;
        for( i = 0; i < A.k; i ++ ) {
            H[ A.pri[i] ] = cas;
        }

        for( i = 0; i < B.k; i ++ ) {
            if( H[ B.pri[i] ] != cas ) {
                L ++;
            }
        }

        memset( zty, 0, sizeof( zty ) );

        int ans = 0;
        for( i = 0; i < A.k; i ++ ) {
            for( j = 0; j < B.k; j ++ ) {
                if( A.pri[i] == B.pri[j] ) {
                    ans += ABS( A.num[i] - B.num[j] );
                    zty[j] = 1;
                    break;
                }
            }

            if( j == B.k ) {
                ans += A.num[i];
            }
        }

        for( j = 0; j < B.k; j ++ ) {
            if( !zty[j] ) {
                ans += B.num[j];
            }
        }

        printf("%d. %d:%d\n", cas, L, ans );


    }
    return 0;
}

