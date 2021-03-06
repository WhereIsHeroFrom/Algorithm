#include <iostream>
#include <cmath>

using namespace std;


struct point3D {
    double x, y, z;
    point3D() {}
    point3D ( double _x, double _y, double _z ) {
        x = _x; y = _y; z = _z;
    }
};

double Sqr( double x ) {
    return x * x;
}

double find(double *a, point3D p ) {
    return a[0] * p.x + a[1] * p.y + a[2] * p.z;
}
// (p.x,p.y,p.z) 绕穿过远点的轴线(u.x,u.y,u.z)-(0,0,0)旋转sita度后的点的坐标
// 从原点往(u.x,u.y,u.z)看sita为顺时针
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

int main() {
    double x, y, z, ux, uy, uz, sita;
    while (scanf("%lf %lf %lf", &x, &y, &z) == 3) {
        scanf("%lf %lf %lf", &ux, &uy, &uz);
        scanf("%lf", &sita);
        point3D X = solve( point3D(x,y,z), point3D( ux, uy, uz ), sita);
        printf("%.3lf %.3lf %.3lf\n", X.x, X.y, X.z );
    }
    return 0;
}

