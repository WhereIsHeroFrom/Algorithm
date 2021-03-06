#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define LL __int64

LL Min;
int buf[ 100010 ], ans[ 100010 ];
LL Smal, Big;
int n ,m;

struct Pai {
    int index;
    int Val;
}a[ 100010 ], b[ 100010 ];

int cmp1( const void *a, const void *b ) {
    Pai *c = ( Pai * )a;
    Pai *d = ( Pai * )b;
    return c->Val - d->Val;
}

int cmp2( const void *a, const void *b ) {
    Pai *c = ( Pai * )a;
    Pai *d = ( Pai * )b;
    return c->index - d->index;
}

struct point {
    int index;
    LL Sum;

    bool friend operator < ( point a, point b ) {
        return a.Sum > b.Sum;
    }
};

priority_queue < point > q;

void Process() {

    int i;
    while( !q.empty() ) 
        q.pop();

    point temp;
    for(i = 0; i < m; i++) {
        temp.Sum = 0;
        temp.index = i;
        q.push( temp );
    }

    Smal = Big = -1;

    for(i = 0; i < n; i++) {
        point temp = q.top();
        q.pop();
        buf[ a[i].index ] = temp.index;
        temp.Sum += ( LL ) a[i].Val;
        q.push( temp );
    }

    while( !q.empty() ) {
        temp = q.top();
        q.pop();

        if( Smal == -1 || temp.Sum < Smal )
            Smal = temp.Sum;

        if( Big == -1 || temp.Sum > Big )
            Big = temp.Sum;
    }

    if( Min == -1 || Big - Smal < Min ) {
        Min = Big - Smal;
        for(i = 0; i < n; i++) {
            ans[i] = buf[i];
        }
    }

    //printf("%I64d\n", Min);
}

int main() {

    int i;
    int t;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i].Val);
            a[i].index = i;
        }
        Min = -1;

        // 1
        Process();

        // 2
        qsort( a, n, sizeof( Pai ), cmp1 );
        Process();

        // 3
        for(i = 0; i < n / 2; i++) {
            Pai tp = a[i];
            a[i] = a[n-1-i];
            a[n-1-i] = tp;
        }
        Process();

        // 4
        for(i = 0; i < n; i++) {
            int x = rand() % n;
            int y = rand() % n;
            Pai tp = a[x];
            a[x] = a[y];
            a[y] = tp;
        }
        Process();

        qsort( a, n, sizeof( Pai ), cmp2 );

        printf("%d\n", n);
        for(i = 0; i < n; i++) {
            if( i )
                printf(" ");
            printf("%d", ans[i] );
        }
        puts("");
    }
    return 0;
}
