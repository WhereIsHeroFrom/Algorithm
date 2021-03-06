#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

#define pi acos(-1.0)
using namespace std;

#define MAXP 1005
#define eps    1e-8

#define SEG_CROSS_TYPE_NONE  0 
#define SEG_CROSS_TYPE_ON    1
#define SEG_CROSS_TYPE_CROSS 2

class Point2D;
typedef Point2D vector2D;

class Point2D {
public:
    double x, y;
    Point2D () {
        x = 0, y = 0;
    }
    Point2D( double _x, double _y ) {
        x = _x;
        y = _y;
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
    void write() {
        printf("%lf %lf\n", x, y);
    }
    
    Point2D operator+(const Point2D& p) {
        return Point2D(x + p.x, y + p.y);
    }
    Point2D operator-(const Point2D& p) {
        return Point2D(x - p.x, y - p.y);
    }
    double operator*(const Point2D& p) {
        return x * p.x + y * p.y; 
    }
    double operator^(const Point2D& p) {
        return x * p.y - y * p.x;
    }
    double dist(const Point2D& p) {
        Point2D q = *this - p;
        return sqrt( q.x*q.x + q.y*q.y );
    }    
    Point2D operator*(const double& val) {
        return Point2D(x * val, y * val); 
    }
    bool operator==(const Point2D& other) {
        return fabs(x-other.x) < eps && fabs(y-other.y) < eps;
    }
    void zerotest() {
        if( fabs(x) < eps ) x = 0;
        if( fabs(y) < eps ) y = 0;
    }
};

// a * x + b * y + c = 0
class lineTriple {
public:
    double a, b, c;
    lineTriple() {
        a = b = c = 0;
    }
    lineTriple(double _a, double _b, double _c) {
        a = _a, b = _b, c = _c;
    }
    lineTriple(Point2D p1, Point2D p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1 ^ p2;
    }
    void write() {
        printf("a = %lf b = %lf c = %lf\n", a, b, c );
    }
    bool operator==(const lineTriple& other) const {
        return fabs(a*other.b-b*other.a) < eps &&\
               fabs(b*other.c-c*other.b) < eps &&\
               fabs(c*other.a-a*other.c) < eps;
    }
    // 需要先用线段判交 预判 线段是否相交 再求交点 
    Point2D crossPoint(const lineTriple& other) const {
        Point2D pt;
        pt.y = - (other.a * c - other.c * a) / ( other.a * b - other.b * a );
        if ( fabs(other.a) < eps ) {
            pt.x = (- b * pt.y - c) / a; 
        }else {
            pt.x = (- other.b * pt.y - other.c) / other.a; 
        }
        pt.zerotest();
        return pt;
    }
};

double Min(double a, double b) {
    return a < b ? a : b;
}

class segment2D {
public:
    Point2D a, b;
    
    void read() {
        a.read();
        b.read();
    }
    
    segment2D(){}
    segment2D(Point2D _a, Point2D _b) {
        a = _a;
        b = _b;
    }
    
    int threeVal( double e ) {
        if (fabs(e) < eps) {
            return 0;
        }else if (e > 0 ) {
            return 1;
        }else {
            return -1;
        }
    }

    double nearestDistWithPoint(Point2D pt) {
        Point2D k = (a - b);
        Point2D t = Point2D(-k.y, k.x);
        segment2D seg( pt + t * 1000000.0, pt - t * 1000000.0 );
        
        double ans = Min(a.dist(pt), b.dist(pt));
        if( !( segCrossWith(seg) == SEG_CROSS_TYPE_NONE ) ) {
            lineTriple tmp(a,b);
            double dist = fabs(pt.x*tmp.a + pt.y*tmp.b + tmp.c) / sqrt( tmp.a*tmp.a + tmp.b*tmp.b );
            ans = Min( ans, dist);
        }
        return ans;
    }
        
    int segCrossWith(segment2D target) {
        int d1,d2,d3,d4;
        double s1,s2,s3,s4;
        
        s1 = (b - a) ^ (target.a - a);
        s2 = (b - a) ^ (target.b - a);
        s3 = (target.b - target.a) ^ (a - target.a);
        s4 = (target.b - target.a) ^ (b - target.a);
        
        d1 = threeVal(s1);
        d2 = threeVal(s2);
        d3 = threeVal(s3);
        d4 = threeVal(s4);
        
        if(d1 * d2 == -1 && d3 * d4 == -1) {
            return SEG_CROSS_TYPE_CROSS;
        }
        if ( d1 == 0 && (a - target.a) * (b - target.a) <= 0 ||
             d2 == 0 && (a - target.b) * (b - target.b) <= 0 ||
             d3 == 0 && (target.a - a) * (target.b - a) <= 0 ||
             d4 == 0 && (target.a - b) * (target.b - b) <= 0
            ) {
            return SEG_CROSS_TYPE_ON;
        }
        return SEG_CROSS_TYPE_NONE;
    } 
};



class Polygon {
public:
    int sta[MAXP];      //在凸包上点的下标
    Point2D point[MAXP];
    bool flag[MAXP];
    int top, n, stab;            //n为读入的点的个数,top-1为凸包上点的个数,0 -- top-2是凸包上点的坐标,top-1和0存的都是第一个点.

    Polygon() { top = n = 0; }
    
    static bool cmp(const Point2D& A,const Point2D& B) { 
        return A.x < B.x || A.x == B.x && A.y < B.y;
    }
    void convexHull(bool f);           //求凸包上的点,f为true表示求的包括边上的点*
    void getpoint(int i,bool f);
    
    bool isInConvexHull(Point2D p);
    void printConvexHull();
    
    double length();
private:
    // 要检测的点是否在栈顶边的右侧
    bool is_right_point(int index, bool f) {
        Point2D pt1 = point[index] - point[ sta[top-2] ];
        Point2D pt2 = point[ sta[top-1] ] - point[ sta[top-2] ];
        double xPro = pt1 ^ pt2;
        if (f) {
            return xPro > 0.0 || fabs(xPro) < eps;
        }
        return xPro > 0.0;
    }
};

void Polygon::getpoint(int i, bool f)
{
    if(top == stab || is_right_point(i, f) ) {
        sta[top++] = i;
        flag[i] = false;
    }
    else {
        
        do {
            top --;
            flag[sta[top]] = true;
        }while ( top > stab && !is_right_point(i, f) );
        
        sta[top++] = i;
        flag[i] = false;
    }
}

void Polygon::convexHull(bool f) {
    int i;
    memset(flag, true, n + 1);
    sort(point, point + n, cmp);
    sta[0] = 0;
    sta[1] = 1;
    top = 2;
    flag[1] = false;
    stab = 1;
    for(i = 2; i < n; i++) 
        getpoint(i, f);
    stab = top;
    for(i = n-2; i >= 0; i--) 
        if(flag[i]) 
            getpoint(i,f);
}

void Polygon::printConvexHull() {
    for(int i = 0; i < top; i++) {
        printf("%lf %lf\n", point[ sta[i] ].x, point[ sta[i] ].y );
    }    
}

double Polygon::length() {
    double ans = 0;
    for(int i = 0; i < top-1; i++) {
        ans += point[ sta[i] ].dist( point[ sta[i+1] ] );
    }
    return ans;
}

bool Polygon::isInConvexHull(Point2D p) {
    segment2D ak(p, Point2D(-12121134.93248, 5433411216.767343) );
    int ans = 0;
    for(int i = 0; i < top - 1; i++) {
        segment2D tar(point[ sta[i] ], point[ sta[i+1] ]);
        int crossResult = ak.segCrossWith(tar);
        if (crossResult == SEG_CROSS_TYPE_ON) {
            return false;
        }else if(crossResult == SEG_CROSS_TYPE_CROSS) {
            ans ^= 1;
        }
    }
    return ans != 0;
}


class lineSeg {
public:
    int y;
    double x1, x2;
    
    lineSeg() {}
    lineSeg(int _y, double _x1, double _x2) {
        y = _y;
        x1 = _x1;
        x2 = _x2;
    }
};
    
int getLatticeVal(double x) {
    if(x < 0) {
        return int(x - eps);
    }else {
        return int(x + eps);
    }
}

Polygon P;
int main() {
    
    // test
    //lineTriple A( Point2D(-7,-7), Point2D(7,7) );
    //lineTriple B( Point2D(6,-6), Point2D(-6,6) );
    //A.crossPoint(B).write();
    //B.crossPoint(A).write();
        
    int t;
    int i;
    
    scanf("%d", &t);
    while( t-- ) {
        int c, n;
        scanf("%d %d", &c, &n);
        P.n = n;
        for(i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            P.point[i] = Point2D(x, y);
        }
        P.point[n] = P.point[0];
        vector <Point2D> inter;
        vector <lineSeg> ans;
        
        for(int y = getLatticeVal(P.point[0].y-1); ; y--) {
            segment2D seg( Point2D(-100000000.0, y), Point2D(1000000000.0, y) );
            inter.clear();
    
            for(i = 0; i < P.n; i++) {
                segment2D tar( P.point[i], P.point[i+1] );
                int crossResult = seg.segCrossWith(tar);
                // 不相交的不管（包括平行） 
                if (crossResult == SEG_CROSS_TYPE_NONE) {
                    continue;
                } 
                // 共线的不管 
                lineTriple A(seg.a, seg.b);
                lineTriple B(tar.a, tar.b);

                if( A == B ) {
                    break;
                } 
                inter.push_back( A.crossPoint(B) );               
            }
            sort(inter.begin(), inter.end(), Polygon::cmp);
            
            if(i < P.n) continue;

            if(inter.size() > 1) {
                double l = inter[0].x;
                double r = inter[ inter.size()-1 ].x;
                
                
                if( fabs( l - getLatticeVal(l) ) < eps ) {
                    l = getLatticeVal(l) + 1;
                }else {
                    l = ceil(l);
                }
                
                if( fabs( r - getLatticeVal(r) ) < eps ) {
                    r = getLatticeVal(r) - 1;
                }else {
                    r = floor(r);
                }  
                
                if(l <= r) {
                    ans.push_back( lineSeg(y, l, r) ); 
                }            
                
            }else if( inter.size() == 0) {
                break;
            }
        }
        
        printf("%d %d\n", c, ans.size());
        for(i = 0; i < ans.size(); i++) {
            printf("%d %.0lf %.0lf\n", ans[i].y, ans[i].x1, ans[i].x2);
        }
    }
    return 0;
}


/*
100
1 8 
5 10 
8 9 
11 6 
10 2 
6 0 
1 1 
0 4 
2 8 
2 4 
3 10 
13 7 
10 -3 
0 0 
3 3 
1 3 
3 1 
1 1 
4 3 
1 4 
4 1 
1 1 
5 4 
0 6 
2 3 
3 0 
1 3 
6 6 
1 3 
3 3 
4 2 
3 1 
1 1 
0 2
*/

