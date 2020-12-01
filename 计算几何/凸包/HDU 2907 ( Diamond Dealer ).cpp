#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-8
#define maxn 100

struct point {
    double x, y;
    int index;
};

class ConvexHull {
    
public:
    int sta[ maxn ];
    point p[ maxn ];
    bool flag[ maxn ];
    int n, top;     // top-1 为凸包上的点的个数，0和top-1存的都是第一个点
    int It;
    ConvexHull() { top = n = 0; }
    static bool cmp( const point &A, const point &B ) {
        return A.x < B.x || fabs( A.x - B.x ) < eps && A.y < B.y;
    }
    void PointSelect( bool f );
    void GetPoint( int i, bool f );
    bool Mult( point O, point A, point B, bool f  );
};

// 向量叉乘, > 0 表示左转
bool ConvexHull ::Mult( point O, point A, point B, bool f  ) {
    A.x -= O.x; A.y -= O.y;
    B.x -= O.x; B.y -= O.y;
    if( f )
        return fabs( A.x * B.y - A.y * B.x ) < eps ||  A.x * B.y - A.y * B.x > 0;
    return  A.x * B.y - A.y * B.x > 0;
}
void ConvexHull::GetPoint( int i, bool f ) {
    while( top > It && !Mult( p[ sta[top-2] ], p[i], p[ sta[top-1] ], f ) ) {
        top --;
        flag[ sta[ top ] ] = true;
    }
    sta[ top++ ] = i;
    flag[i] = false;
}
void ConvexHull::PointSelect( bool f ) {
    int i;
    for( i = 0; i < n; i++ ) flag[i] = true;
    sort( p, p + n, cmp );
    sta[0] = 0;
    sta[1] = 1;
    top = 2;
    flag[1] = false;
    for( It = 1, i = 2; i < n; i ++ ) GetPoint(i, f);
    for( It = top, i = n-2; i >= 0; i-- ) 
        if( flag[i] ) GetPoint(i, f);
}

ConvexHull C, T;

int order[ maxn ];

int main() {
    int t, i;
    int p, q;

    scanf("%d", &t );
    while( t-- ) {
        scanf("%d %d %d", &p, &q, &C.n );
        for( i = 0; i < C.n; i ++ ) {
            scanf("%lf %lf", &C.p[i].x, &C.p[i].y );
            C.p[i].index = i;
        }
        T = C;
        C.PointSelect( false );
        for( i = 0; i < C.top; i ++ ) {
            order[i] = C.p[ C.sta[i] ].index;
            //printf("%d\n", order[i] );
        }
        int v = 0, s = 0;
        for( i = 0; i < C.top - 1; i ++ ) {
            int ab = order[i+1] - order[i];
            if( ab < 0 ) ab = -ab;
            
            if( ab == 1 || ab == T.n - 1 )
                s ++;
            else
                v ++;
        }
        //printf("%d %d\n", v, s );
        int ans = - p * v + q * s;
        if( ans < 0 ) ans = 0;


        printf("%d\n", ans );
    }
    return 0;
}
