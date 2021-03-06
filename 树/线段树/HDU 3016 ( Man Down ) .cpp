#include <iostream>
#include <vector>
using namespace std;

#define maxn 100100 
#define BLACK 100000000
#define COMPLEX -1 

struct point {
    int h;
    int xl, xr;
    int val;
}p[ maxn ];

vector < int > vec[ maxn ];
int color[ maxn * 4 ];
// 颜色覆盖说明 COMPLEX 表示该区间有混合颜色 BLACK 表示一种无用色  其他 表示可用色
int hash[ maxn ];
int Count = 0;

int cmp( const void *a, const void *b ) {
    point *c = ( point *)a;
    point *d = ( point *)b;
    return c->h < d->h ? 1 : -1;
}

void Read( int n ) {
    int i;
    for(i = 0; i < n; i++) {
        scanf("%d %d %d %d", &p[i].h, &p[i].xl, &p[i].xr, &p[i].val );
    }
    qsort( p, n, sizeof( point ), cmp );
}

// 询问前一次的点能否到达当前点
void Query( int p, int a, int b, int l, int r, int index ) {
    
    if( color[p] != COMPLEX ) {
        if( color[p] != BLACK ) {
            if( hash[ color[p] ] != Count ) {
                hash[ color[p] ] = Count;
                vec[ color[p] ].push_back ( index );
            }
        }
        return ;
    }

    int mid = ( a + b ) / 2;

    if( r <= mid ) {
        Query( 2*p, a, mid, l, r, index );
    }else if( l > mid ) {
        Query( 2*p+1, mid+1, b, l, r, index );
    }else {
        Query( 2*p, a, mid, l, mid, index );
        Query( 2*p+1, mid+1, b, mid+1, r, index );
    }
}
// 用当前线段来覆盖区域
void Insert( int p, int a, int b, int l, int r, int index ) {
    

    if( a == l && r == b ) {
        color[ p ] = index;
        return ;
    }

    if( color[p] != COMPLEX ) {
        color[2*p] = color[2*p+1] = color[p];
        color[p] = COMPLEX;
    }

    int mid = ( a + b ) / 2;

    if( r <= mid ) {
        Insert( 2*p, a, mid, l, r, index );
    }else if( l > mid ) {
        Insert( 2*p+1, mid+1, b, l, r, index );
    }else {
        Insert( 2*p, a, mid, l, mid, index );
        Insert( 2*p+1, mid+1, b, mid+1, r, index );
    }
}

int dp[ maxn ];

int main() {
    int i, j;
    int n;
    while( scanf( "%d", &n ) != EOF ) {
        for(i = 0; i <= n; i++) {
            vec[i].clear();
        }
        Read(n);    
        p[n].h = 0;
        p[n].xl = 1; p[n].xr = 100000;
        p[n].val = 0;
        n ++;

        for( i = 1; i < maxn * 4; i ++ )
            color[i] = BLACK;

        for( i = 0; i < n; i++ ) {
            Count ++;
            Query( 1, 1, 100000, p[i].xl, p[i].xr, i );

            Insert( 1, 1, 100000, p[i].xl, p[i].xl, i );
            Insert( 1, 1, 100000, p[i].xr, p[i].xr, i );

            if( p[i].xl + 1 < p[i].xr )
                Insert( 1, 1, 100000, p[i].xl+1, p[i].xr-1, BLACK );
        }

        memset( dp, -1, sizeof( dp ) );
        dp[0] = 100 + p[0].val;

        for(i = 0; i < n - 1; i++) {
            if( dp[i] > 0 ) {
                for( j = 0; j < vec[i].size(); j ++ ) {
                    int to = vec[i][j];
                    if( dp[i] + p[ to ].val > dp[ to ] )
                        dp[ to ] = dp[i] + p[ to ].val;
                }
            }
        }

        printf("%d\n", dp[n-1] );
    }
    return 0;
}


