#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-15
#define  pi acos(-1.0)
#define maxn 510
#define inf 999999999.0

struct point {
    double x, y;
    point() {}
    point( double _x, double _y ) {
        x = _x; y = _y;
    }
};
struct Triple {
    double a, b, c;
};

point operator+( point a, point b ) {
    return point( a.x+b.x, a.y+b.y);
}
point operator-( point a, point b ) {
    return point( a.x-b.x, a.y-b.y);
}
double operator*( point a, point b ) {
    return a.x*b.y - a.y*b.x;
}

bool EQ( double x, double y ) {
    return fabs( x - y ) < eps;
}
bool EQ( point a, point b ) {
    return ( EQ(a.x, b.x) && EQ(a.y, b.y) ); 
}
bool EQ( Triple A, Triple B ) {
    return EQ(A.a*B.b,B.a*A.b)&&EQ(A.b*B.c,B.b*A.c) && EQ(A.c*B.a,B.c*A.a);
}
bool LT( double a, double b ) {
    return ( !EQ(a, b) && (a < b) );
}
bool LEQ( double a, double b ) {
    return ( LT(a, b) || EQ(a, b) );
}
double Sqr(double x) {
    return x * x;
}
double Sqr( point A ) {
    return A.x * A.x + A.y * A.y;
}
double Dist( point a, point b ) {
    return sqrt( Sqr(a.x - b.x) + Sqr( a.y - b.y ) );
}
int three(double d) {
    if(fabs(d) < eps )return 0;
    else if(d>0)return 1;
    else return -1; 
}
Triple TwoPoint_OneLine ( point A, point B ) {
    Triple o;
    o.a = ( B.y - A.y );
    o.b = - ( B.x - A.x );
    o.c = A.y * B.x - A.x * B.y;
    return o;
}
point TwoLine_OnePoint( Triple A, Triple B ) {
    point C;
    C.y = (A.a * B.c - B.a * A.c) / ( B.a * A.b - A.a * B.b );
    C.x = (A.b * B.c - B.b * A.c) / ( A.a * B.b - B.a * A.b );
    return C;
}

// 计算多边形面积
double Area( point *p, int n ) {
    double A = 0; if( n < 3 ) return 0; p[n] = p[0];
    for( int i = 0; i < n; i ++ ) A += p[i] * p[i+1];
    return fabs( A / 2 );
}

// 两个特殊三角形的交(分别有一个点在原点)
// 保证b在a的逆时针方向或者共线，d在c的逆时针方向或者共线。
double Triangle_Intersect_Triangle( point a, point b, point c, point d, int n, int m ) {
    point tmp[10], p1[4], p2[4];
    p1[0] = point(0,0); p1[1] = a; p1[2] = b;
    p2[0] = point(0,0); p2[1] = c; p2[2] = d;
    int tn, i = 0, j, next, now;
    p1[n] = p1[0]; p2[m] = p2[0];

    for(i = 0; i < n && m > 2; i++ ) {
        now = three( (p1[i+1] - p1[i]) * ( p2[0] - p1[i+1] ) );
        for(j = tn = 0; j < m; j++, now = next) {
            if( now >= 0 ) tmp[tn++] = p2[j];
            next = three( (p1[i+1] - p1[i]) * ( p2[j+1] - p1[i+1] ) );
            if( now * next < 0 ) {
                Triple C = TwoPoint_OneLine( p1[i], p1[i+1] );
                Triple D = TwoPoint_OneLine( p2[j], p2[j+1] );
                tmp[tn++] = TwoLine_OnePoint( C, D );
            }
        }
        for(j = 0; j < tn; j ++ ) p2[j] = tmp[j];
        m = tn; p2[m] = p2[0];
    }
    if(m < 3) return 0.0;
    return Area(p2, m);
}

double Poly_Intersect_Poly( point *S, point *T, int n, int m ) {
    int i, j;
    int f[2];
    double Sum = 0;
    point O( 0, 0 ), tmp;
    point a, b, c, d;
    S[n] = S[0]; T[m] = T[0];
    for( i = 0; i < n; i ++ ) {
        a = S[i]; b = S[i+1];
        if( EQ( O, a ) || EQ( O, b ) ) continue;
        f[0] = three( a * b );
        if( !f[0] ) continue;           // 退化为直线
        if( f[0] < 0 ) {
            tmp = a; a = b; b = tmp;
        }
        for( j = 0; j < m; j ++ ) {
            c = T[j]; d = T[j+1];
            if( EQ( O, c ) || EQ( O, d ) ) continue;
            f[1] = three( c * d );
            if( !f[1] ) continue;       // 退化为直线
            if( f[1] < 0 ) {
                tmp = c; c = d; d = tmp;
            }
            Sum += f[0]*f[1]*Triangle_Intersect_Triangle(a,b, c,d, 3, 3 );
        }
    }
    return fabs(Sum);
}

point S[1000], T[1000];
int n, m;

int main() {
    int i, j;

    while( scanf( "%d %d", &n, &m ) != EOF ) {
        for( i = 0; i < n; i ++ ) {
            scanf("%lf %lf", &S[i].x, &S[i].y );
        }
        for( i = 0; i < m; i ++ ) {
            scanf("%lf %lf", &T[i].x, &T[i].y );
        }
        double Sum = 0;
        Sum += Area( S, n ) + Area( T, m );
        Sum -= Poly_Intersect_Poly( S, T, n, m );
        printf("%.2lf\n", fabs( Sum ) );
    }
    return 0;

}
