#include <iostream>
#include <cmath>

using namespace std;

#define eps 1e-6
#define pi acos(-1.0)

struct point3D {
    double x, y, z;
    point3D () {
    }
    point3D( double _x, double _y, double _z ) {
        x = _x; y = _y; z = _z;
    }
};

struct Sphere {
    double x, y, z;
    point3D now;
    double r;
};

double Sqr( double x ) {
    return x * x;
}

double Dist( point3D a, point3D b ) {
    return sqrt( Sqr(a.x-b.x) + Sqr(a.y-b.y) + Sqr(a.z-b.z) );
}

double operator*( point3D a, point3D b ) {
    return a.y * b.z + a.x * b.y + a.z * b.x - a.y * b.x - a.x * b.z - a.z * b.y;
}
double operator&( point3D a, point3D b ) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
point3D operator-( point3D from, point3D to ) {
    return point3D( from.x-to.x, from.y-to.y, from.z-to.z );
}
point3D operator+( point3D from, point3D to ) {
    return point3D( to.x+from.x, to.y+from.y, to.z+from.z );
}


point3D Unit( point3D from, point3D to ) {
    double all = Dist( from, to );
    to.x = (to.x - from.x) / all;
    to.y = (to.y - from.y) / all;
    to.z = (to.z - from.z) / all;
    return to;
}

bool EQ( double x, double y ) {
    return fabs( x - y ) < eps;
}
bool EQ( point3D a, point3D b ) {
    return EQ(a.x, b.x) && EQ(a.y, b.y ) && EQ( a.z, b.z );
}
bool LT(double x, double y ) {
    return (x < y) && !EQ(x,y);
}

/* 判断点是否在Sphere上 */
bool IsOnSphere( point3D n, Sphere Sp ) {
    return EQ( Sqr(Sp.r), Sqr( n.x-Sp.x ) + Sqr( n.y-Sp.y ) + Sqr( n.z-Sp.z ) );
}

// 直线和球体的交
/*只要将z分量变为0就变成了直线和圆的交了*/
/*
直线用两点式表示 l 和 r
-1 不相交
0  相切   交点保存在p中
1  相交   交点保存在p,q中
*/

int Line_Intersect_Sphere( point3D l, point3D r, Sphere Sp, point3D& p, point3D& q ) {
    
    if( LT( Dist( Sp.now, l ), Dist( Sp.now, r ) ) ) {
        point3D tmp = l; l = r; r = tmp;
    }

    point3D lvec = Unit( l, r );
    point3D svec = Unit( l, Sp.now );
    double dis = Dist( Sp.now, l );
    double alpha = (lvec & svec);
    double a, b, c;

    a = 1;
    b = - 2.0 * dis * alpha;
    c = Sqr( dis ) - Sqr( Sp.r );

    double delt = Sqr(b) - 4*a*c;
    if( delt < 0 ) return -1;

    dis = (- b + sqrt( delt ) ) / 2;
    p = point3D( l.x + lvec.x * dis, l.y + lvec.y * dis, l.z + lvec.z * dis);
    dis = (- b - sqrt( delt ) ) / 2;
    q = point3D( l.x + lvec.x * dis, l.y + lvec.y * dis, l.z + lvec.z * dis);
    if( EQ( delt, 0 ) ) return 0;

    return 1;
}

/* 射线交球体 */
/* 注意：射线是有方向的，所以from和to不可混淆 */
/*
-1 未射中
 0 相切
 1 射中    碰撞点保存在p中，并且出射向量保存在q中 
*/

int Ray_Intersect_Sphere( point3D from, point3D to, Sphere Sp, point3D& p, point3D& q ) {
    point3D buf[2];
    int state = Line_Intersect_Sphere( from, to, Sp, buf[0], buf[1] );
    if( state == -1 ) {
        return -1;
    }else if( state == 0 ) {
        if( LT( ( to - from)&( buf[0] - from ), 0 ) )
            return -1;
        return 0;
    }else {
        if( LT( ( to - from)&( buf[0] - from ), 0 ) )
            return -1;
        p = buf[0];
        if( LT( Dist( from, buf[1] ) , Dist( from, buf[0] ) ) ) {
            p = buf[1];
        }
        // 入射向量单位化
        point3D Ia = Unit( from, to );
        Ia = ( point3D(0, 0, 0) - Ia );
        // 中心向量单位化
        point3D Ib = Unit( Sp.now, p );
        double dot = (Ia & Ib);

        // 对称点的轴中心
        point3D Ic( p.x + Ib.x * dot * Dist( from, p ),
        p.y + Ib.y * dot * Dist( from, p ),
        p.z + Ib.z * dot * Dist( from, p ) );

        q = point3D(2*Ic.x, 2*Ic.y, 2*Ic.z) - from;
        q = Unit( p, q );
        return 1;
    }
}

int n;
point3D from, to;
Sphere I[ 1000 ];

int main() {
    int i;

    while( scanf( "%d", &n ) != EOF && n ) {
        from = point3D( 0, 0, 0 );
        scanf("%lf %lf %lf", &to.x, &to.y, &to.z );
        for( i = 0; i < n; i ++ ) {
            scanf("%lf %lf %lf %lf", &I[i].x, &I[i].y, &I[i].z, &I[i].r );
            I[i].now = point3D( I[i].x, I[i].y, I[i].z );
        }

        int Count = 0;
        while( Count < 5 ) {

            double Min = -1;
            point3D ansP, ansQ;

            for( i = 0; i < n; i ++ ) {
                point3D p, q;
                int state = Ray_Intersect_Sphere( from, to, I[i], p, q );
                if( state == 1 ) {
                    if( EQ( Dist(from, p), 0 ) ) continue;

                    if( Min < 0 || Dist(from, p) < Min ) {
                        Min = Dist( from, p );
                        ansP = p;
                        ansQ = q;
                    }
                }
            }
            if( Min < 0 )
                break;

            Count ++;
            from = ansP;
            to = ansP + ansQ;
        }
        printf("%.6lf %.6lf %.6lf\n", from.x, from.y, from.z );

    }
    return 0;
}

