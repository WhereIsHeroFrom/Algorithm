#include <iostream>

using namespace std;

struct point {
    int x, y;
    point() {
    }
    point ( int _x, int _y ) {
        x = _x;
        y = _y;
    }
};

struct Rec {
    point l, r;
};

Rec rec[ 1000 ];
int n, m;

bool EQ( point a, point b ) {
    return (a.x==b.x) && (a.y==b.y);
}

int main() {
    int cas = 1;
    int i;

    while( scanf( "%d", &n ) != EOF && n ) {
        for( i = 0; i < n; i ++ ) {
            scanf( "%d %d %d %d", &rec[i].l.x, &rec[i].l.y, &rec[i].r.y, &rec[i].r.x );
            rec[i].r.x += rec[i].l.x - 1;
            rec[i].r.y += rec[i].l.y - 1;
        }

        printf("Desktop %d:\n", cas ++ );
        scanf("%d", &m );

        while( m-- ) {
            int x, y;

            scanf("%d %d", &x, &y );

            for( i = n-1; i >= 0; i-- ) {
                if( rec[i].l.x <= x && x <= rec[i].r.x 
                    && rec[i].l.y <= y && y <= rec[i].r.y 
                    )
                    break;
            }

            if( i == -1 )
                printf("background\n");
            else
                printf("window %d\n", i+1 );
        }
    }
    return 0;
}

