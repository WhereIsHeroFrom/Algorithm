#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// 数据量大的时候需要修改精度
#define eps 1e-9
#define maxn 2010
#define pi acos( -1.0 )
#define inf (987654321.0*987654321.0)

struct point {
    double x, y;
    point () {}
    point ( double _x, double _y ) {
        x = _x; y = _y;
    }
    int index; 
};
struct Triple {
    double a, b, c;
};

//左转平面系的 半平面 结构
/*
由from到to的线段，以及在该线段的左边区域所组成的半平面
alph为to相对于from的极角
要求给出的多边形呈逆时针排列（也就是传说中的面积大于0）
*/
struct halfplane {
    point from, to;
    double alph;
    halfplane() {}
    halfplane( point _f, point _t ) {
        from = _f; to = _t;
    }
    void CalcAlph() {
        alph = atan2( to.y-from.y, to.x-from.x );
    }
};

inline bool EQ( double x, double y ) {
    return fabs( x-y ) < eps;
}
inline bool EQ( point a, point b ) {
    return ( EQ(a.x, b.x) && EQ(a.y, b.y) ); 
}
inline bool EQ( Triple A, Triple B ) {
    return EQ(A.a*B.b,B.a*A.b)&&EQ(A.b*B.c,B.b*A.c) && EQ(A.c*B.a,B.c*A.a);
}
inline bool LT( double a, double b ) {
    return ( !EQ(a, b) && (a < b) );
}
inline bool LEQ( double a, double b ) {
    return ( EQ(a,b) || LT(a,b) );
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

// p0经过p1左转后到p2返回true
inline bool JudgeLeft( point p2, point p0, point p1 ) {
    return LEQ( ( p2 - p0 ) * ( p1 - p0 ), 0 );
}
// 两半平面边沿线求交点
point HalfInterPoint( halfplane a, halfplane b ) {
    Triple C, D;
    C = TwoPoint_OneLine( a.from, a.to );
    D = TwoPoint_OneLine( b.from, b.to );
    return TwoLine_OnePoint( C, D );
}
// 判断a和b的交点在不在x的半平面内，在的话返回true
bool IsInPlane( halfplane a, halfplane b, halfplane x ) {
    return JudgeLeft( HalfInterPoint(a, b), x.from, x.to );
}
// 极角排序，相同极角取最左边的
bool cmp( halfplane a, halfplane b ) {
    if( EQ( a.alph, b.alph ) ) 
        return JudgeLeft( a.from, b.from, b.to );
    return a.alph < b.alph;
}
halfplane hp[ maxn ];
int deq[ 2*maxn ], front, rear;    // 双端队列
point p[ maxn ];

/* > 0 表示点的排列为逆时针排列 */
double Area( point *ans, int n ) {
    int i;
    double area = 0;
    ans[n] = ans[0];
    for( i = 0; i < n; i ++ ) {
        area += ans[i] * ans[i+1];
    }
    return area / 2;
}
double HalfPlaneIntersection( halfplane *hp, int n ) {
    int i, cnt;
    // 添加半平面的边界
    
    hp[ n++ ] = halfplane( point( -inf, -inf ), point( inf, -inf ) );
    hp[ n++ ] = halfplane( point(  inf, -inf ), point( inf,  inf ) );
    hp[ n++ ] = halfplane( point(  inf,  inf ), point( -inf, inf ) );
    hp[ n++ ] = halfplane( point( -inf,  inf ), point( -inf, -inf ) );
    
    for( i = 0; i < n; i ++ ) {
        hp[i].CalcAlph();
    }
    sort( hp, hp + n, cmp );
    cnt = 1;
    for( i = 1; i < n; i ++ ) {
        if( !EQ( hp[i].alph, hp[i-1].alph ) )
            hp[ cnt++ ] = hp[i];
    }
    front = 0;
    rear = 1;
    deq[front] = 0;
    deq[rear] = 1;

    // 注意：在判断和删除的时候都是先对rear进行，再对front进行，否则会出错
    for( i = 2; i < cnt; i ++ ) {
    // 双端队列的尾部两个半平面的交点是否在hp[i]这个半平面内，不在则尾指针--
        while( front < rear && !IsInPlane( hp[deq[rear]], hp[deq[rear-1]], hp[i] ) )
            rear --;
    // 双端队列的头部两个半平面的交点是否在hp[i]这个半平面内，不在则头指针++
        while( front < rear && !IsInPlane( hp[deq[front]], hp[deq[front+1]], hp[i] ) )
            front ++;
        deq[ ++rear ] = i;
    }
    // 删除多余半平面
    while( front < rear && !IsInPlane( hp[deq[rear-1]], hp[deq[rear]], hp[ deq[front] ] ) )
        rear --;
    while( front < rear && !IsInPlane( hp[deq[front]], hp[deq[front+1]], hp[ deq[rear] ] ) )
        front ++;
    if( front == rear ) return 0;
    /*这个情况尤其小心
        hp[0] = halfplane( point(0,0), point(1,1) );
        hp[1] = halfplane( point(0,1), point(1,0) );
        hp[2] = halfplane( point(1,0), point(0,-0.5) );
    */
    n = 0;
    for( i = front; i < rear; i++ ) {
        p[ n++ ] = HalfInterPoint( hp[ deq[i] ], hp[ deq[i+1] ] );
    }
    p[ n++ ] = HalfInterPoint( hp[ deq[front] ], hp[ deq[rear] ] );
    return Area( p, n );
}

int main() {
    int i;
    int n, t;
    while( scanf( "%d", &n ) != EOF ) {
        for( i = 0; i < n; i++ ) {
            int x, y;
            scanf("%d %d", &x, &y );
            p[i] = point( x, y );
        }
        p[n] = p[0];
        double pre = Area( p, n );
        if( pre > 0 ) {
            for( i = 0 ;i < n; i ++ ) {
                hp[i] = halfplane( p[i], p[i+1] );
            }
        }else {
            for( i = 0 ; i < n; i ++ ) {
                hp[i] = halfplane( p[i+1], p[i] );
            }
        }
        printf( "%.1lf%%\n", 100 * fabs( HalfPlaneIntersection( hp, n ) / pre ) );
    }
    return 0;
}

