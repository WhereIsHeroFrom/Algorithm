#include <iostream>

using namespace std;

#define LL __int64
#define N 101

int f[ N ], prime[ N ], L[ N ], Lj[ N ], Sum[ N ], size;
int HASH[ 1000 ];
int J[ N ];            // 2^n
int n;


// L[ i ] 表示它所在的位 前面有L[i] 个0
// Lj[i] 表示当前有多少位

struct point {
    int Max;
    int Min;
}tree[ 300010 ];

int A[ 100010 ];

int Calc( int key ) {

    int res = 0;
    int i;

    for(i = 0; i < size; i++) {
        if( key % prime[i] == 0 ) {
            int C = 1;
            key /= prime[i];
            while( key % prime[i] == 0 ) {
                key /= prime[i];
                C ++;
            }
            res |= C * J[ L[i] ];
        }

        if( !f[ key ] ) {
            int id = HASH[ key ];
            res |= J[ L[ id ] ];
            key = 1;
        }
        if( key == 1 )
            return res;
    }
}

int Max( int a, int b ) {
    int i;
    int res = 0;
    for(i = 0; i < 4; i++) {
        int M1, M2;
        M1 = (a & Sum[i]);
        M2 = (b & Sum[i]);
        res |= ( M1 > M2 ? M1 : M2 );
    }
    res |= ( (a | b) & ( (J[21]-1) << 10 ) );
    return res;
}

int Min( int a, int b ) {
    int i;
    int res = 0;
    for(i = 0; i < 4; i++) {
        int M1, M2;
        M1 = (a & Sum[i]);
        M2 = (b & Sum[i]);
        res |= ( M1 < M2 ? M1 : M2);
    }
    res |= ( (a & b) & ( (J[21]-1) << 10 ) );
    return res;
}


void Init() {
    int i, j;
    f[0] = f[1] = 1;

    for(i = 2; i < N; i++) {
        if( !f[i] ) {
            prime[ size++ ] = i;
            HASH[ i ] = size - 1;
            for(j = i+i; j < N; j += i ) {
                f[j] = 1;
            }
        }
    }

    J[0] = 1;
    for( i = 1; i < 100; i ++ ) {
        J[i] = J[i-1] * 2;
    }

    Sum[0] = 7;
    L[0] = 0;
    Lj[0] = 3;

    for(i = 1; i < size; i++) {
        int p = 1;
        int Count = -1;
        while( p < 100 ) {
            p *= prime[i];
            Count ++;
        }

        L[i] = L[i-1] + Lj[i-1];

        if( Count <= 1 ) {
            Lj[i] = 1;
            Sum[i] = 1 * J[ L[i] ];
        }else if( Count <= 3 ) {
            Lj[i] = 2;
            Sum[i] = 3 * J[ L[i] ];
        }else if( Count <= 7 ) {
            Lj[i] = 3;
            Sum[i] = 7 * J[ L[i] ];
        }
    }


}

point Build( int p, int l, int r ) {
    if( l == r ) {
        point temp;
        temp.Max = temp.Min = Calc( A[l] );
        return temp;
    }
    point T;
    int mid;

    mid = ( l + r ) / 2;

    tree[ 2*p ] = Build( 2*p, l, mid );
    tree[ 2*p+1 ] = Build( 2*p+1, mid+1, r );

    T.Max = Max( tree[ 2*p ].Max, tree[ 2*p+1 ].Max );
    T.Min = Min( tree[ 2*p ].Min, tree[ 2*p+1 ].Min );
    return T;
}

point Query( int p, int a, int b, int l, int r ) {

    if( a == l && r == b ) {
        return tree[p];
    }

    int mid = ( a + b ) / 2;
    point T, A, B;

    if( r <= mid ) {

        T = Query( 2*p, a, mid, l, r );

    }else if( mid + 1 <= l ) {

        T = Query( 2*p+1, mid+1, b, l, r );

    }else {

        A = Query( 2*p, a, mid, l, mid );
        B = Query( 2*p+1, mid+1, b, mid+1, r );

        T.Max = Max( A.Max, B.Max );
        T.Min = Min( A.Min, B.Min );
    }
    return T;
}

point Update( int p, int l, int r, int pos, int C) {

    if( l == r && l == pos ) {
        tree[p].Max = tree[p].Min = Calc( C );
        return tree[p];
    }

    int mid = ( l + r ) / 2;

    if( pos >= mid + 1 ) {
        tree[ 2*p+1 ] = Update( 2*p+1, mid+1, r, pos, C );
    }else {
        tree[ 2*p ] = Update( 2*p, l, mid, pos, C );
    }
    tree[p].Max = Max( tree[2*p].Max, tree[2*p+1].Max );
    tree[p].Min = Min( tree[2*p].Min, tree[2*p+1].Min );

    return tree[p];
}

char str[ 20 ];
int x, y;

LL Pro( int key, LL p ) {
    int i;
    LL S = 1 % p;
    for(i = 0; i < size; i++) {
        int ee = (key & Sum[i]);
        ee /= J[ L[i] ];

        while( ee-- ) {
            S *= ( LL ) prime[i];
            if( S >= p ) {
                S %= p;
            }
        }
    }
    return S;
}

int main() {
    Init();
    int m;
    int i;
    LL P;
    point RT;

    while( scanf( "%d %d", &n, &m ) != EOF ) {

        for(i = 1; i <= n; i++) {
            scanf("%d", &A[i]);
        }
        tree[1] = Build( 1, 1, n );



        while( m-- ) { 
            scanf( "%s", str );
            if( strcmp ( str, "L" ) == 0 ) {

                scanf("%d %d %I64d", &x, &y, &P );
                RT = Query( 1, 1, n, x, y );

                int tt = Pro( RT.Max, P );
                if( tt == 1 && P == 1 ) {
                    while(1)
                        ;
                }

                printf("%I64d\n", tt );


            }else if( strcmp ( str, "G" ) == 0 ) {

                scanf("%d %d %I64d", &x, &y, &P );
                RT = Query( 1, 1, n, x, y );
                
                int tt = Pro( RT.Min, P );

                if( tt == 1 && P == 1 ) {
                    while(1)
                        ;
                }

                printf("%I64d\n", tt );

            }else {
                scanf("%d %d", &x, &y);
                tree[1] = Update( 1, 1, n, x, y );
            }
        }

    }
    return 0;
}

/*
6 4
1 2 4 5 6 3
L 2 3 1000

*/
