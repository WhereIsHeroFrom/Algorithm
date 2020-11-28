#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-9
#define maxn 210

struct point {
    double x, y;
    point() {
    }
    point( double _x, double _y ) {
        x = _x;
        y = _y;
    }
};

struct polygon {
    point arr[maxn];
    int n;
};

// 凸包只有一个点的时候会出问题，只有一个点不满足 
// top-1 为凸包上的点的个数，0和top-1存的都是第一个点的情况
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
    if( n == 1 ) {
        top = 2;
        sta[0] = 0;
        sta[1] = 0;
        return ;
    }
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

bool EQ( double x, double y ) {
    return fabs( x - y ) < eps;
}
bool LT( double a, double b ) {
    return ( !EQ(a, b) && (a < b) );
}
bool LEQ( double a, double b ) {
    return ( LT(a, b) || EQ(a, b) );
}

// 向量加
point operator+( point a, point b ) {
    return point( a.x+b.x, a.y+b.y);
}
// 向量减
point operator-( point a, point b ) {
    return point( a.x-b.x, a.y-b.y);
}
// 叉积
double operator*( point a, point b ) {
    return a.x*b.y - a.y*b.x;
}
// 点积
double operator&( point a, point b ) {
    return a.x*b.x + a.y*b.y;
}

bool JudgeLeft( point p2, point p0, point p1 ) {
    return LEQ( ( p2 - p0 ) * ( p1 - p0 ), 0 );
}

int three(double d) {
    if(fabs(d) < eps )return 0;
    else if(d>0)return 1;
    else return -1; 
}
double cross(point a,point b,point c) {
   return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
double between(point a,point b,point c) {
    return (a.x-b.x)*(a.x-c.x)+(a.y-b.y)*(a.y-c.y);
}
int segcross(point a,point b,point c,point d) {
    int d1,d2,d3,d4;
    double s1,s2,s3,s4;
    d1=three(s1=cross(a,b,c));
    d2=three(s2=cross(a,b,d));
    d3=three(s3=cross(c,d,a));
    d4=three(s4=cross(c,d,b));
    if(d1*d2==-1&&d3*d4 == -1)return 1;
    if(d1==0&&between(c,a,b) <= 0 ||
        d2==0&&between(d,a,b) <= 0 ||
        d3==0&&between(a,c,d) <= 0 ||
        d4==0&&between(b,c,d) <= 0
        )return 2;
    return 0;
}


int InPolygon( point p, polygon& S ) {
    int i;
    int C = 0;
    point tmp( -3123414.0, 23423424.0 );
    S.arr[ S.n ] = S.arr[0];
    for( i = 0; i < S.n; i ++ ) {
        int u = segcross( tmp, p, S.arr[i], S.arr[i+1] );
        if( u == 2 ) 
            return 2;
        C += u;
    }
    return (C & 1);
}

point S[maxn], T[maxn], N[maxn];
ConvexHull C;
polygon son;
int map[maxn][maxn];
int n, m, top;

int main() {
    int i, j, k;

    while( scanf( "%d %d", &n, &m ) != EOF ) {
        for( i = 0; i < n; i ++ ) {
            scanf("%lf %lf", &S[i].x, &S[i].y );
        }
        C.n = m;
        for( i = 0; i < m; i ++ ) {
            scanf("%lf %lf", &T[i].x, &T[i].y );
            C.p[i] = T[i];
        }
        C.PointSelect( false );
        son.n = C.top - 1;
        for( i = 0; i < son.n; i ++ ) {
            son.arr[i] = C.p[ C.sta[i] ];
        }
        son.arr[ son.n ] = son.arr[0];

        top = 0;
        for( i = 0; i < n; i ++ ) {
            if( InPolygon( S[i], son ) ) {
                N[ top ++ ] = S[i];
            }
        }

        for( i = 0; i < m; i++ ) {
            for( j = 0; j < m; j ++ ) {
                map[i][j] = 10000;
            }
        }

        for( i = 0; i < m; i ++ ) {
            for( j = 0; j < m; j ++ ) {
                if( i != j ) {
                    for( k = 0; k < top; k ++ ) {
                        if( JudgeLeft( N[k], T[i], T[j] ) )
                            break;
                    }
                    if( k == top ) {
                        map[i][j] = 1;
                        //printf("%d %d\n", i, j );
                    }
                }
            }
        }

        for( k = 0; k < m; k ++ ) {
            for( i = 0; i < m; i ++ ) {
                for( j = 0; j < m; j ++ ) {
                    if( map[i][k] + map[k][j] < map[i][j] )
                        map[i][j] = map[i][k] + map[k][j];
                }
            }
        }

        int Min = 10000;
        for( i = 0; i < m; i ++ ) {
            if( map[i][i] < Min )
                Min = map[i][i];
        }

        //printf("%d %d\n", top, Min );
        if( Min == 10000 )
            printf("0\n");
        else {
            printf( "%d\n", top * 173 - Min * 47 < 0 ? 0 : top * 173 - Min * 47 );
        }
    }
    return 0;
}

/*
1 2
0 0
1 1
2 2


1 2
0 0
-1 -1
1 1
*/
