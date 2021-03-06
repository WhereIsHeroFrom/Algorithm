#include <iostream>
#include <cmath>
#include <map>

#define MAXN 200
using namespace std;

int t;
int pre[ MAXN ];
int num[ MAXN ];
int T;
int mech[ MAXN ];
map < int, int > Map;
int hash[ MAXN ][ MAXN ];
int n;

struct point {
    int u;
    int v;
    int val;
} E[ MAXN * MAXN ];
int top = 0;

int cmp( const void *a, const void *b ) {
    point *c = ( point *)a;
    point *d = ( point *)b;
    return - c->val + d->val;
}


int find( int key ) {
    while( pre[ key ] != key )
        key = pre[ key ];
    return key;
}

int Union( int p1, int p2 ) {
    
    int s1 = find( p1 );
    int s2 = find( p2 );

    if( s1 == s2 )
        return 0;

    if( num[ s1 ]  >= num[ s2 ] ) {
        num[ s1 ] += num[ s2 ];
        pre[ s2 ] = s1;
    }else {
        num[ s2 ] += num[ s1 ];
        pre[ s1 ] = s2;
    }

    return 1;
}


int main() {

    int i, j;
    int A, mec, all, nex;

    scanf("%d", &t);

    while( t-- ) {
        T = 1;
        memset( hash, 0, sizeof( hash ));
        Map.clear();
        scanf("%d", &n);

        top = 0;

        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &A, &mec, &all);
            int u = Map[ A ];
            if( !u ) {
                u = Map[ A ] = T++;
            }
            mech[ u ] = mec;

            int rt;
            for(j = 0; j < all; j++) {
                scanf("%d", &rt);
                int v = Map[ rt ];
                if( !v ) {
                    v = Map[ rt ] = T++;
                }
                hash[ u ][ v ] = 1;
            }
        }


        int sum = 0;

        for(i = 1; i < T; i++) {
            for(j = 1; j < T; j++) {
                if( i != j && hash[i][j] ) {
                    E[ top ].u = i;
                    E[ top ].v = j;
                    E[ top++ ].val = mech[i] + mech[j];
                    sum += mech[i] + mech[j];
                }
            }
        }
        sum /= 2;
        
        qsort( E, top, sizeof( point ), cmp );

        for(i = 1; i < T; i++) {
            pre[i] = i;
            num[i] = 1;
        }

        int ty = 0;

        for(i = 0; i < top; i++) {
            if( Union( E[i].u, E[i].v ) ) {
                ty ++;
                sum -= E[i].val;
                if( ty == n-1 )
                    break;
            }
        }

        printf("%d\n", sum);
    }

    return 0;
}

/*
7
0 3 2
1 2

1 3 2
0 3

2 1 2
0 3

3 1 4
1 2 4 5

4 1 2
3 6

5 2 2
3 6

6 2 2
4 5
*/
