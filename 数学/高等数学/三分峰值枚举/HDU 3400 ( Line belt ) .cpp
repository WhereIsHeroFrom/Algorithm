#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) {
        x = _x; y = _y;
    }
}pt[4];

int P, Q, R;

// 0 <= pos <= 1
Point CalcPoint(Point A, Point B, double pos) {
    return Point( A.x + (B.x - A.x) * pos, A.y + (B.y - A.y) * pos );
}

double Sqr(double X) {
    return X * X;
}

double Dist(Point A, Point B) {
    return sqrt( Sqr(A.x-B.x) + Sqr(A.y-B.y) );
}

double CaclDist(Point st, Point md, Point en) {
    return Dist(st, md)/R + Dist(md, en)/Q;
}

double TripleDivide(Point st) {
    double l = 0, r = 1;
    double ml, mr;

    while(l + 1e-6 < r) {
        ml = (2 * l + r) / 3;
        mr = (l + 2 * r) / 3;

        double ld = CaclDist(st, CalcPoint(pt[2], pt[3], ml), pt[3]);
        double rd = CaclDist(st, CalcPoint(pt[2], pt[3], mr), pt[3]);

        if(ld > rd) {
            l = ml;
        }else 
            r = mr;
    }
    return CaclDist(st, CalcPoint(pt[2], pt[3], (l+r)/2), pt[3]);
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 4; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            pt[i].x = x;
            pt[i].y = y;
        }

        scanf("%d %d %d", &P, &Q, &R);
        double all = Dist(pt[0], pt[1]);
        double l = 0, r = 1;
        double ml, mr;
        double ans = 1e20;
        while(l + 1e-6 < r) {
            ml = (2 * l + r) / 3;
            mr = (l + 2 * r) / 3;
            
            double ld = all*ml/P + TripleDivide( CalcPoint(pt[0], pt[1], ml) );
            double rd = all*mr/P + TripleDivide( CalcPoint(pt[0], pt[1], mr) );
        
            if(ld > rd) {
                l = ml;
            }else 
                r = mr;

            if(ld < ans) ans = ld;
            if(rd < ans) ans = rd;
        }

        printf("%.2lf\n", ans);
    }
    return 0;
}
