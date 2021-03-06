#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define pi acos(-1.0)
#define MAXP 50010
#define eps    1e-8

#define SEG_CROSS_TYPE_NONE  0 
#define SEG_CROSS_TYPE_ON    1
#define SEG_CROSS_TYPE_CROSS 2

class Point2D;
typedef Point2D vector2D;

bool zero(double x) {
    return fabs(x) < eps;
} 

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
    double getY(double x) {
        return (-c - a*x) / b;
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

int c[MAXP];
 
int lowbit(int x) {
    return x & (-x);
}

void add(int x, int val, int c[]) {
    while( x < MAXP ) {
        c[x] += val;
        x += lowbit(x);
    }
}

int sum(int x, int c[]) {
    int sum = 0;
    while( x > 0 ) {
        sum += c[x];
        x -= lowbit(x);
    }
    return sum;    
}

segment2D seg[MAXP];

class Interval {
    public:
        double l, r;
        Interval(){}
        Interval(double _l, double _r) {
            l = _l;
            r = _r;
        }

};

int cmp(const Interval& a, const Interval& b) {
    return a.l > b.l;
}

Interval inv[ MAXP ];

double findY[MAXP];
int findYCnt = 0;
int sameVal[ MAXP ];
int getV(double y) {
    int l = 0, r = findYCnt - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if( zero(findY[mid] - y) ) return mid + 1;
        if(y < findY[mid]) r = mid - 1;
        else l = mid + 1;
    }
}

int main() {
    int n;
    double l, r;
    int i, j;
    while( scanf("%d", &n) != EOF ) {
        memset(c, 0, sizeof(c));
        memset(sameVal, 0, sizeof(sameVal));
        int pYCnt = 0;
        int newC = 0;
        int tmpC = 0;
        // 需要考虑垂直X轴的情况，即b == 0的情况 记录个数为 pYCnt  
        scanf("%lf %lf", &l, &r);
        for(i = 0; i < n; i++) {
            seg[i].read();
            lineTriple T(seg[i].a, seg[i].b);
            //T.write();
            if( zero(T.b) ) {
                double tmp = -T.c / T.a;
                if( l + eps < tmp && tmp < r - eps ) {
                    pYCnt ++; 
                }
            }else {
                // 直线在(l, r)区间的y坐标 
                inv[ newC ] = Interval( T.getY(l), T.getY(r) );
                findY[ tmpC++ ] = inv[ newC ].r;
                newC ++;
            } 
        }
        findYCnt = 1;
        sort(findY, findY + tmpC);
        for(i = 1; i < tmpC; i++) {
            if( !zero(findY[i] - findY[i-1]) ) {
                findY[ findYCnt++ ] = findY[i];
            }
        }

        sort(inv, inv + newC, cmp);
        for(i = 0; i < newC; i++) {
            int nowIndex = getV( inv[i].r );
            sameVal[ nowIndex ] ++;
        }
        /*for(i = 0; i < findYCnt; i++) {
            printf("%lf %d\n", findY[i], sameVal[i+1]);
        }    */
        int ans = pYCnt * newC;  // 垂直于X轴的直线和所有这些直线有交点 
        int preinsert = 0;
        for(i = 0; i < newC; i++) {
            int nowIndex = getV( inv[i].r );
            //printf("(%lf %lf %d)\n", inv[i].l, inv[i].r, nowIndex);
            
            if(i && !zero(inv[i].l - inv[i-1].l) ) {
                for(j = preinsert; j < i; j++) {
                    int preIndex = getV( inv[j].r );
                    add(preIndex, 1, c);
                }
                preinsert = i;
            }
            
            ans += sum(nowIndex-1, c);
        }
        printf("%d\n", ans ); 
    }
    
    return 0;
}

/*
9
0.0 1.0
0.0 0.0 1.0 1.0
0.0 2.0 1.0 2.0
0.0 2.5 2.5 0.0
0.0 2.5 1.0 9.9
0.0 2.2 1.0 2.2
0.0 3.2 1.0 2.2
0.5 9 0.5 10
0.6 9 0.6 10
0.7 19 0.7 10
*/

