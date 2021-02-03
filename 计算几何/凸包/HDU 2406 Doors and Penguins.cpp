#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

//************************* 计算几何 模板 *************************
// 包含：
// 1、凸包
// 2、线段判交
// 3、点在多边形内
// 4、多边形交判定

const int MAXP = 100010;
const double eps = 1e-10;
#define INT_POINT

// 两线段交点类型
enum SegCrossType {
    SCT_NONE = 0,
    SCT_CROSS = 1,         // 正常相交
    SCT_ENDPOINT_ON = 2,   // 其中一条线段的端点在另一条上
};

#ifdef INT_POINT
typedef int PointType;
typedef long long BigPointType;    // 由于乘法可能导致 int 溢出，所以需要定义一种乘法后的类型(平方、叉乘、点乘)
#else
typedef double PointType;
typedef double BigPointType;
#endif
typedef int PointIndex;

// 小于
bool ST(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a < b;
#else
    return a - b < -eps;
#endif
}

// 等于
bool EQ(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a == b;
#else
    return fabs(a - b) < eps;
#endif
}

// 大于
bool LT(BigPointType a, BigPointType b) {
    return !ST(a, b) && !EQ(a, b);
}

int TernaryFunc(double v) {
    if (EQ(v, 0)) {
        return 0;
    }
    return ST(v, 0) ? -1 : 1;
}

BigPointType SQR(BigPointType x) {
    return x * x;
}

class Point2D {
public:
    Point2D() : x_(0), y_(0) {}
    Point2D(PointType x, PointType y) : x_(x), y_(y) {}

    bool zero() const;
    Point2D operator + (const Point2D& pt) const;
    Point2D operator - (const Point2D& pt) const;
    BigPointType operator * (const Point2D& pt) const;
    BigPointType cross(const Point2D& pt) const;
    bool operator < (const Point2D& pt) const;
    bool operator == (const Point2D& pt) const;


    BigPointType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
    double getAngle() const;
    int getIndex() const;

    Point2D getMinusYPoint() const;
private:
    PointType x_, y_;
    double angle_;            // 相对于左下角点的极角
    double distSqr_;          // 相对于左下角点的距离平方
    int index_;               // 在原数组的下标，方便索引用
};
typedef Point2D Vector2D;

bool Point2D::zero() const {
    return EQ(x_, 0) && EQ(y_, 0);
}

Point2D Point2D::operator + (const Point2D& pt) const {
    return Point2D(x_ + pt.x_, y_ + pt.y_);
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}

BigPointType Point2D::operator * (const Point2D& pt) const {
    return x_ * pt.x_ + y_ * pt.y_;
}

BigPointType Vector2D::cross(const Vector2D& pt) const {
    return (BigPointType)x_ * pt.y_ - (BigPointType)y_ * pt.x_;
}

bool Point2D::operator<(const Point2D& pt) const {
    // 1. 第一关键字： y 小的
    // 2. 第二关键字： x 小的
    if (!EQ(y_, pt.y_)) {
        return ST(y_, pt.y_);
    }
    return ST(x_, pt.x_);
}

bool Point2D::operator==(const Point2D& pt) const {
    return (*this - pt).zero();
}

BigPointType Point2D::distSquare(const Point2D& pt) const {
    Point2D t = *this - pt;
    return SQR(t.x_) + SQR(t.y_);
}

bool Point2D::angleCmp(const Point2D& a, const Point2D& b) {
    if (fabs(a.angle_ - b.angle_) < eps) {
        return a.distSqr_ < b.distSqr_;
    }
    return a.angle_ < b.angle_;
}

void Point2D::calculateAngle(const Point2D& o) {
    Point2D t = *this - o;
    if (t.zero()) {
        // 该情况下 atan2 是 undefined 的，需要单独处理
        angle_ = 0;
        distSqr_ = 0;
    }
    else {
        angle_ = atan2(0.0 + t.y_, 0.0 + t.x_); // 这里 y >= 0 是能保证的，所以值在 [0, PI] 之间
        distSqr_ = distSquare(o);
    }
}

void Point2D::read(int idx) {
#ifdef INT_POINT
    scanf("%d %d", &x_, &y_);
#else
    scanf("%lf %lf", &x_, &y_);
#endif
    index_ = idx;
}

void Point2D::print() {
#ifdef INT_POINT
    printf("%d %d\n", x_, y_);
#else
    printf("%lf %lf", x_, y_);
#endif
}

double Point2D::getAngle() const {
    return angle_;
}

int Point2D::getIndex() const {
    return index_;
}

Point2D Point2D::getMinusYPoint() const
{
    return Point2D(x_, -y_);
}

class Segment2D {
public:
    Segment2D(){}
    Segment2D(Point2D from, Point2D to) : from_(from), to_(to) {}
    BigPointType cross(const Point2D& p) const;
    bool lineCross(const Segment2D& other) const;
    bool pointOn(const Point2D& p) const;
    SegCrossType segCross(const Segment2D& other);
private:
    Point2D from_, to_;
};

// 定点叉乘
// 外部找一点p，然后计算 (p-s) X (t-s)
BigPointType Segment2D::cross(const Point2D& p) const {
    return (p - from_).cross(to_ - from_);
}

// 跨立测验
// 将当前线段作为一条很长的直线，检测线段other是否跨立在这条直线的两边
bool Segment2D::lineCross(const Segment2D& other) const {
    return TernaryFunc(cross(other.from_)) * TernaryFunc(cross(other.to_)) == -1;
}

// 点是否在线段上
bool Segment2D::pointOn(const Point2D& p) const {
    // 满足两个条件：
    //  1.叉乘为0，    (p-s)×(t-s) == 0
    //  2.点乘为-1或0，(p-s)*(p-t) <= 0
    return TernaryFunc(cross(p)) == 0 && TernaryFunc((p - from_) * (p - to_)) <= 0;
}

// 线段判交
// 1.通过跨立测验
// 2.点是否在线段上
SegCrossType Segment2D::segCross(const Segment2D& other) {
    if (this->lineCross(other) && other.lineCross(*this)) {
        // 两次跨立都成立，则必然相交与一点
        return SCT_CROSS;
    }
    // 任意一条线段的某个端点是否在其中一条线段上，四种情况
    if (pointOn(other.from_) || pointOn(other.to_) ||
        other.pointOn(from_) || other.pointOn(to_)) {
        return SCT_ENDPOINT_ON;
    }
    return SCT_NONE;
}


class Polygon {
private:
    void grahamScan_Pre();   // 计算凸包前的准备工作
    void grahamScan_Post(bool flag, Polygon& ret);  // 填充凸包的点到给定的多边形
public:
    bool isPoint() const;                      // 求完凸包以后判断是否是一个点
    bool isLine() const;                       // 求完凸包以后判断是否是一条线
    bool isPointIn(const Point2D& pt) const;   // 判断点是否在多边形内；
    bool isIntersectWithPolygon(Polygon &o);   // 判断是否和另个一多边形有交集；
    void grahamScan(bool flag, Polygon& ret);
    double area();
    double length();
    int size();
    void clear();
    void addPoint(const Point2D& pt);
public:
    //bool check(Polygon& o);           // 根据不同情况提供的开放接口
private:
    int n_;
    Point2D point_[MAXP];
    PointIndex stack_[MAXP];
    int top_;
};

bool Polygon::isPoint() const  {
    if (n_ <= 1) {
        return true;
    }
    return point_[n_ - 1] == point_[0];
}

bool Polygon::isLine() const {
    if (n_ <= 2) {
        return true;
    }
    return (TernaryFunc((point_[n_ - 1] - point_[0]).cross(point_[1] - point_[0])) == 0);
}


bool Polygon::isPointIn(const Point2D& pt) const {
    Point2D inf(123456543, 132543876);
    Segment2D judge(pt, inf);
    int isIn = 0;
    for (int i = 0; i < n_; ++i) {
        if (Segment2D(point_[i], point_[i + 1]).segCross(judge) != SCT_NONE) {
            isIn ^= 1;
        }
    }
    return isIn;
}

bool Polygon::isIntersectWithPolygon(Polygon& o) {
    // 1. 两个多边形的边有交集，返回 false
    for (int i = 0; i < n_; ++i) {
        Segment2D srcSeg(point_[i], point_[i + 1]);
        for (int j = 0; j < o.n_; ++j) {
            Segment2D tarSeg(o.point_[j], o.point_[j + 1]);
            if (srcSeg.segCross(tarSeg) != SCT_NONE) {
                return false;
            }
        }
    }

    // 2. 一个多边形的点在另一个多边形内
    for (int i = 0; i < n_; ++i) {
        if (o.isPointIn(point_[i])) {
            return false;
        }
    }

    for (int i = 0; i < o.n_; ++i) {
        if (isPointIn(o.point_[i])) {
            return false;
        }
    }

    return true;
}

void Polygon::grahamScan_Pre()
{
    // 1. 首先将最下面的那个点（如果y相同，则取最左边）找出来放到 point_[0] 的位置
    for (int i = 1; i < n_; ++i) {
        if (point_[i] < point_[0]) {
            swap(point_[i], point_[0]);
        }
    }
    // 2. 对 point_[0] 计算极角
    for (int i = 1; i < n_; ++i) {
        point_[i].calculateAngle(point_[0]);
    }
    // 3. 极角排序
    sort(point_ + 1, point_ + n_, Point2D::angleCmp);
}


void Polygon::grahamScan_Post(bool flag, Polygon& ret) {
    ret.n_ = top_;
    for (int i = 0; i < top_; ++i) {
        ret.point_[i] = point_[stack_[i]];
    }

    if (ret.isPoint() || ret.isLine()) {
        // 是点或者线的情况不进行补点
        return;
    }

    // Graham 扫描算法的改进，如果要考虑边上的点
    // 那么最后一条多边形的回边
    if (flag) {
        for (int i = n_ - 1; i >= 0; --i) {
            if (point_[i] == ret.point_[top_ - 1]) continue;
            if (fabs(point_[i].getAngle() - ret.point_[top_ - 1].getAngle()) < eps) {
                // 极角相同的点必须补回来
                ret.point_[ret.n_++] = point_[i];
            }
            else break;
        }
    }
    // 构成回路
    ret.point_[ret.n_] = ret.point_[0];
}

// flag 是否算上边上的点、重复点
void Polygon::grahamScan(bool flag, Polygon& ret) {

    // 找到极值坐标系原点，并且按照极角排序
    grahamScan_Pre();

    // 栈底永远是那个极值坐标系的原点
    top_ = 0;
    stack_[top_++] = 0;

    for (int i = 1; i < n_; ++i) {
        if ((point_[i] - point_[0]).zero()) {
            // 和原点有重合，即多点重复
            if (flag) {
                stack_[top_++] = i;
            }
            continue;
        }

        while (top_ >= 2) {
            Point2D p1 = point_[stack_[top_ - 1]] - point_[stack_[top_ - 2]];
            Point2D p2 = point_[i] - point_[stack_[top_ - 2]];
            BigPointType crossRet = p1.cross(p2);
            // 如果选择边上的点，那么叉乘结果大于等于0是允许的
            // 如果不选择边上的点，那么叉乘结果大于0是允许的
            if (flag && TernaryFunc(crossRet) < 0 || !flag && TernaryFunc(crossRet) <= 0)
                --top_;
            else
                break;
        }
        stack_[top_++] = i;
    }

    grahamScan_Post(flag, ret);
}

double Polygon::area() {
    double ans = 0;
    point_[n_] = point_[0];
    for (int i = 1; i < n_; ++i) {
        ans += (point_[i] - point_[0]).cross(point_[i + 1] - point_[0]);
    }
    return ans / 2;
}

double Polygon::length() {
    if (n_ == 1) {
        return 0;
    }
    else if (n_ == 2) {
        return sqrt(0.0 + point_[1].distSquare(point_[0])) * 2;
    }
    double ans = 0;
    point_[n_] = point_[0];
    for (int i = 0; i < n_; ++i) {
        ans += sqrt(0.0 + point_[i].distSquare(point_[i + 1]));
    }
    return ans;
}

int Polygon::size() {
    return n_;
}

void Polygon::clear() {
    n_ = 0;
    top_ = 0;
}

void Polygon::addPoint(const Point2D& pt) {
    point_[n_++] = pt;
}

//************************* 计算几何 模板 *************************

Polygon D, P, DRes, PRes;

int main() {
    int n, p;
    Point2D s, t;
    int cas = 0;
    int x1, y1, x2, y2;
    while (scanf("%d %d", &n, &p) != EOF && (n || p)) {
        if (cas++) puts("");
        D.clear();
        P.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            D.addPoint(Point2D(x1, y1));
            D.addPoint(Point2D(x1, y2));
            D.addPoint(Point2D(x2, y1));
            D.addPoint(Point2D(x2, y2));
        }
        for (int i = 0; i < p; ++i) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            P.addPoint(Point2D(x1, y1));
            P.addPoint(Point2D(x1, y2));
            P.addPoint(Point2D(x2, y1));
            P.addPoint(Point2D(x2, y2));
        }
        D.grahamScan(false, DRes);
        P.grahamScan(false, PRes);
        bool ans = DRes.isIntersectWithPolygon(PRes);
        printf("Case %d: %s\n", cas, ans ? "It is possible to separate the two groups of vendors." : "It is not possible to separate the two groups of vendors.");
    }
    return 0;
}