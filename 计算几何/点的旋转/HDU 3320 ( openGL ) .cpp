#include <iostream>
#include <cmath>

using namespace std;

#define pi acos (-1.0)
int t;
char str[ 100000 ][50];
int top;

struct point3D {
    double x, y, z;
    point3D() {
    }
    point3D ( double _x, double _y, double _z ){
        x = _x;
        y = _y;
        z = _z;
    }
};

point3D operator +( point3D a, point3D b ) {
    return point3D( a.x+b.x, a.y+b.y, a.z+b.z );
}

point3D operator *( point3D a, point3D b ) {
    return point3D( a.x*b.x, a.y*b.y, a.z*b.z );
}

double Sqr( double x ) {
    return x * x;
}

double find(double *a, point3D p ) {
    return a[0] * p.x + a[1] * p.y + a[2] * p.z;
}
//(p.x,p.y,p.z) 绕穿过原点的轴线(u.x,u.y,u.z)旋转sita度后的点的坐标
//从原点往(u.x,u.y,u.z)看sita为顺时针
point3D solve( point3D p, point3D u, double sita ) {
    double t = sqrt(Sqr(u.x) + Sqr(u.y) + Sqr(u.z));
    u.x /= t, u.y /= t, u.z /= t;
    double c = cos(sita);
    double s = sin(sita);
    double a[3][3] = {
        {Sqr(u.x) + (1 - Sqr(u.x)) * c, u.x * u.y * (1 - c) - u.z * s, u.x * u.z * (1 - c) + u.y * s},
        {u.x * u.y * (1 - c) + u.z * s, Sqr(u.y) + (1 - Sqr(u.y)) * c, u.y * u.z * (1 - c) - u.x * s},
        {u.x * u.z * (1 - c) - u.y * s, u.y * u.z * (1 - c) + u.x * s, Sqr(u.z) + (1 - Sqr(u.z)) * c}
    };
    return point3D( find(a[0], p), find(a[1], p), find(a[2], p) );
}

point3D now;
point3D K;

int main() {

    int i;

    //freopen( "1006Test.in", "r", stdin );

    scanf("%d", &t);

    while( t-- ) {
        top = 0;
        while( scanf("%s", str[top] ) != EOF ) {
            if( strcmp( str[top], "glEnd();" ) == 0 )
                break;
            top ++;
        }

        for( i = top; i >= 1; i -- ) {
            if( str[i][2] == 'V' ) {
                sscanf(&str[i][11], "%lf,%lf,%lf", &now.x, &now.y, &now.z );
                break;
            }
        }

        for( i = i-1; i >= 0; i-- ) {
            if( str[i][2] == 'T' ) {
                sscanf(&str[i][13], "%lf,%lf,%lf", &K.x, &K.y, &K.z );
                now = now + K;
            }else if( str[i][2] == 'S' ) {
                sscanf(&str[i][9], "%lf,%lf,%lf", &K.x, &K.y, &K.z );
                now = now * K;
            }else if( str[i][2] == 'R' ) {
                double ang;

                sscanf(&str[i][10], "%lf,%lf,%lf,%lf", &ang, &K.x, &K.y, &K.z );
                now = solve( now, K, ang );
            }
        }
        printf("%.1lf %.1lf %.1lf\n", now.x, now.y, now.z );
    }
    return 0;
}

