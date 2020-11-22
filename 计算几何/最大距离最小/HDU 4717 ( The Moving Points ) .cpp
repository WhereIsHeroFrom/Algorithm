#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXP = 110000;
#define PI acos(-1.0)
#define eps 1e-15
#define LL __int64
typedef double Type;

// 三值函数
int threeValue(Type d) {
    if(fabs(d) < 1e-6)
        return 0;
    return d > 0 ? 1 : -1;
}

// 两线段交点类型
enum SegCrossType {
    SCT_NONE = 0,
    SCT_CROSS = 1,         // 正常相交
    SCT_ENDPOINT_ON = 2,   // 其中一条线段的端点在另一条上
};

class Point2D {
    Type x, y;

public:
    Point2D(){
    }
    Point2D(Type _x, Type _y): x(_x), y(_y) {}
    void read() {
        scanf("%lf %lf", &x, &y);
    }
    void print() {
        printf("<%lf, %lf>\n", x, y);
    }
    Type getx() const { return x; }
    Type gety() const { return y; }
    bool inRange(Type xl, Type xr, Type yl, Type yr) const;
    Point2D turnLeft();
    Point2D turnRight();
    double angle();
    Point2D operator+(const Point2D& other) const;
    Point2D operator-(const Point2D& other) const;
    Point2D operator*(const double &k) const;
    Point2D operator/(const double &k) const;
    Type operator*(const Point2D& other) const;
    bool operator <(const Point2D &p) const;
    Type X(const Point2D& other) const;
    double len();
    Point2D normalize();
    bool sameSide(Point2D a, Point2D b);
};

typedef Point2D Vector2D;

double Vector2D::len() {
    return sqrt(x*x + y*y);
}

Point2D Vector2D::normalize() {
    double l = len();
    if(threeValue(l)) {
        x /= l;
        y /= l;
    }
    return *this;
}

bool Point2D::inRange(Type xl, Type xr, Type yl, Type yr) const {
    return xl<=x && x <= xr && yl<=y && y<=yr;
}

Point2D Point2D::turnLeft() {
    return Point2D(-y, x);
}
Point2D Point2D::turnRight() {
    return Point2D(y, -x);
}
double Point2D::angle() {
    return atan2(y, x);
}

Point2D Point2D::operator+(const Point2D& other) const {
    return Point2D(x + other.x, y + other.y);
}

Point2D Point2D::operator-(const Point2D& other) const {
    return Point2D(x - other.x, y - other.y);
}

Point2D Point2D::operator *(const double &k) const {
    return Point2D(x * k, y * k);
}

Point2D Point2D::operator /(const double &k) const {
    return Point2D(x / k, y / k);
}

bool Point2D::operator <(const Point2D &p) const {
    return y + eps < p.y || ( y < p.y + eps && x + eps < p.x );
}

// !!!!注意!!!!
// 如果Type为int，则乘法可能导致int32溢出，小心谨慎
// 点乘
Type Point2D::operator*(const Point2D& other) const {
    return x*other.x + y*other.y;
}
// 叉乘
Type Point2D::X(const Point2D& other) const {
    return x*other.y - y*other.x;
}

// 向量a和b是否在当前向量的同一边
bool Point2D::sameSide(Point2D a, Point2D b) {
    // 请保证 当前向量和a、b向量的起点一致
    return threeValue(X(a)) * threeValue(X(b)) == 1;
}

class Segment2D {
    Point2D s, t;
public:
    Segment2D() {}
    Segment2D(const Point2D& _s, const Point2D& _t) : s(_s), t(_t) {
    }
    void read() {
        s.read();
        t.read();
    }
    Type sXt() const {
        return s.X(t);
    }

    Vector2D vector() const {
        return t - s;
    }

    // 定点叉乘
    // 外部找一点p，然后计算 (p-s)×(t-s)
    Type cross(const Point2D& p) const {
        return (p - s).X(t - s);
    }

    // 跨立测验
    // 将当前线段作为一条很长的直线，检测线段other是否跨立在这条直线的两边
    bool lineCross(const Segment2D& other) const;
    
    // 点是否在线段上
    bool pointOn(const Point2D& p) const;

    // 线段判交
    // 1.通过跨立测验
    // 2.点是否在线段上
    SegCrossType segCross(const Segment2D& other);

    double leastDistFromPoint(const Point2D& pt);
};

bool Segment2D::lineCross(const Segment2D& other) const {
    return threeValue(cross(other.s)) * threeValue(cross(other.t)) == -1;
}

bool Segment2D::pointOn(const Point2D& p) const {
    // 满足两个条件：
    //  1.叉乘为0，    (p-s)×(t-s) == 0
    //  2.点乘为-1或0，(p-s)*(p-t) <= 0
    return cross(p) == 0 && (p-s)*(p-t) <= 0;
}

SegCrossType Segment2D::segCross(const Segment2D& other) {
    if(this->lineCross(other) && other.lineCross(*this)) {
        // 两次跨立都成立，则必然相交与一点
        return SCT_CROSS;
    }
    // 任意一条线段的某个端点是否在其中一条线段上，四种情况
    if(pointOn(other.s) || pointOn(other.t) ||
        other.pointOn(s) || other.pointOn(t) ) {
            return SCT_ENDPOINT_ON;
    }
    return SCT_NONE;
}

class Line2D {
public:
    Point2D a, b;
    Line2D() {}
    Line2D(const Point2D& _a, const Point2D& _b): a(_a), b(_b) {
    }
    Point2D getCrossPoint(const Line2D& );
    bool isParallelTo(const Line2D& );
};

// 两条不平行的直线必有交点
// 利用叉乘求面积法的相似三角形比值得出交点
Point2D Line2D::getCrossPoint(const Line2D& other) {
    double SA = (other.a - a).X(b - a);
    double SB = (b - a).X(other.b - a);
    return (other.b * SA + other.a * SB) / (SA + SB);
}

bool Line2D::isParallelTo(const Line2D& other) {
    return !threeValue( (b-a).X(other.b - other.a) );
}

class line2DTriple {
public:
    // ax + by + c = 0;
    Type a, b, c;

    line2DTriple(){}
    line2DTriple(Type _a, Type _b, Type _c): a(_a), b(_b), c(_c) {
    }
    line2DTriple(const Point2D& _a, const Point2D& _b) {
        getFromSegment2D(Segment2D(_a, _b));
    }
    line2DTriple(const Segment2D& s) {
        getFromSegment2D(s);
    }
    line2DTriple operator+(const line2DTriple& l) const {
        return line2DTriple(a+l.a, b+l.b, c+l.c);
    }
    void getFromSegment2D(const Segment2D&);
    double getPointDist(const Point2D& p);
    void print() {
        printf("%lf %lf %lf\n", a, b, c);
    }

};

void line2DTriple::getFromSegment2D(const Segment2D& seg) {
    Vector2D v = seg.vector();
    a = - v.gety();
    b = v.getx();
    c = seg.sXt();
    //Print();
}

double line2DTriple::getPointDist(const Point2D& p) {
    return fabs(a*p.getx() + b*p.gety() + c) / sqrt(a*a+b*b);
}

// 点到线段的最短距离
double Segment2D::leastDistFromPoint(const Point2D& pt) {
    line2DTriple lt(*this);
    double dist = lt.getPointDist(pt);
    Vector2D v = vector().turnLeft();
    if( threeValue((s - pt).X(v)) * threeValue((t - pt).X(v)) <= 0) {
        return dist;
    }else {
        double a = (s - pt).len();
        double b = (t - pt).len();
        return a < b ? a : b;
    }
}

struct Polygon {
    int n;
    Point2D p[MAXP];

    void print();
    double area();
    void getConvex(Polygon &c);
    bool isConvex();
    bool isPointInConvex(const Point2D &);
    bool isPointInPolygon(const Point2D &);
    Point2D CalcBary();
    void convertToCounterClockwise();
};

void Polygon::print() {
    int i;
    printf("%d\n", n);
    for(i = 0; i < n; ++i) {
        p[i].print();
    }
}

double Polygon::area() {
    double sum = 0;
    p[n] = p[0];
    for ( int i = 0 ; i < n; i ++ )
        sum += p[i].X(p[i + 1]);
    return sum / 2;
}

// 求凸包
void Polygon::getConvex(Polygon &c) {
    sort(p, p + n);
    c.n = n;
    for(int i = 0; i < n; ++i) {
        c.p[i] = p[i];
    }    
    
    if(n <= 2) {
        c.p[n] = p[0];
        return ;
    }
        
    int &top = c.n;
    top = 1;
    for ( int i = 2 ; i < n ; i ++ ) {
        while ( top && threeValue(( c.p[top] - p[i] ).X( c.p[top - 1] - p[i] )) >= 0 )
            top --;
        c.p[++top] = p[i];
    }
    int temp = top;
    c.p[++ top] = p[n - 2];
    for ( int i = n - 3 ; i >= 0 ; i -- ) {
        while ( top != temp && threeValue(( c.p[top] - p[i] ).X( c.p[top - 1] - p[i] )) >= 0 )
            top --;
        c.p[++ top] = p[i];
    }
    c.p[++top] = c.p[0];
}

// 是否凸多边形
bool Polygon::isConvex() {
    bool s[3] = { false , false , false };
    p[n] = p[0], p[n + 1] = p[1];
    for ( int i = 0 ; i < n ; i ++ ) {
        s[threeValue(( p[i + 1] - p[i] ) * ( p[i + 2] - p[i] )) + 1] = true;
        // 叉乘有左有右，肯定是凹的
        if ( s[0] && s[2] ) return false;
    }
    return true;
}

// 点是否在凸多边形内
bool Polygon::isPointInConvex(const Point2D &P) {
    bool s[3] = { false , false , false };
    p[n] = p[0];
    for ( int i = 0 ; i < n ; i ++ ) {
        s[threeValue(( p[i + 1] - P ) * ( p[i] - P )) + 1] = true;
        if ( s[0] && s[2] ) return false;
        if ( s[1] ) return true;
    }
    return true;
}

bool Polygon::isPointInPolygon(const Point2D &P) {
    Point2D maxP(123451.67, 765431.21);
    p[n] = p[0];
    bool inPoly = false;
    for(int i = 0; i < n; ++i) {
        Segment2D now(p[i], p[i+1]);
        SegCrossType sct = now.segCross( Segment2D(P, maxP) );
        if(sct == SCT_ENDPOINT_ON) {
            return true;
        }else if(sct == SCT_CROSS) {
            inPoly = !inPoly;
        }
    }
    return inPoly;
}

// 转成逆时针顺序
void Polygon::convertToCounterClockwise() {
    if(area() >= 0) {
        return ;
    }
    for(int i = 1; i <= n / 2; ++i) {
        Point2D tmp = p[i];
        p[i] = p[n-i];
        p[n-i] = tmp;
    }
}

Point2D Polygon::CalcBary() {
    Point2D ret(0, 0);
    double area = 0;
    p[n] = p[0];
    for ( int i = 0 ; i < n ; i ++ ) {
        double temp = p[i] * p[i + 1];
        if ( threeValue(temp) == 0 ) continue;
        area += temp;
        ret = ret + ( p[i] + p[i + 1] ) * ( temp / 3 );
    }
    return ret / area;
}

Polygon pol, vpol, res, cov;

double calcMaxDist(double time) {
    int i, j;
    res.n = pol.n;
    for(i = 0; i < pol.n; ++i) {
        res.p[i] = pol.p[i] + vpol.p[i] * time;
    }
    res.p[i] = res.p[0];
    res.getConvex(cov);

    double maxDist = -1;
    if(cov.n == 1) {
        return 0;
    }
    for(i = 0; i < cov.n; ++i) {
        for(j = i+1; j < cov.n; ++j) {
            double dist = (cov.p[i] - cov.p[j]).len();
            if(dist > maxDist) {
                maxDist = dist;
            }
        }
    }
    return maxDist;
}



int main() {
    int i;
    int t, cases = 0;
    int n;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        pol.n = vpol.n = n;
        for(i = 0; i < n; ++i) {
            pol.p[i].read();
            vpol.p[i].read();
        }

        double l = 0, r = 10000000000.0;
        while(r - l > 1e-5) {
            double ml = (2*l + r) / 3;
            double mr = (l + 2*r) / 3;

            double mld = calcMaxDist(ml);
            double mrd = calcMaxDist(mr);

            if(mld > mrd) {
                l = ml;
            }else {
                r = mr;
            }
        }
        printf("Case #%d: %.2lf %.2lf\n", ++cases, l, calcMaxDist(l));
    }
    return 0;
}
