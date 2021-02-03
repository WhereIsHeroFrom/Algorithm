#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

//************************* 凸包 grahamScan 模板 *************************


const int MAXP = 100010;
const double eps = 1e-10;
#define INT_POINT

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

class Polygon {
private:
    void grahamScan_Pre();   // 计算凸包前的准备工作
    void grahamScan_Post(bool flag, Polygon& ret);  // 填充凸包的点到给定的多边形
public:
    bool isPoint() const;    // 求完凸包以后判断是否是一个点
    bool isLine() const;     // 求完凸包以后判断是否是一条线
    void grahamScan(bool flag, Polygon& ret);
    double area();
    double length();
    int size();

    void clear();
    void addPoint(const Point2D& pt);
public:
    bool check(int cas);           // 根据不同情况提供的开放接口
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

//************************* 凸包 grahamScan 模板 *************************

bool Polygon::check(int cas) {
    // 1. 不足以组成一个多边形
    if (n_ <= 2) {
        return false;
    }
    point_[n_] = point_[0];
    // 2. 每条边不相等
    BigPointType dist0 = point_[0].distSquare(point_[1]);
    for (int i = 1; i < n_; ++i) {
        if (!EQ(point_[i].distSquare(point_[i + 1]), dist0)) {
            return false;
        }
    }

    // 3. 每个角度不相等
    BigPointType cr = (point_[1] - point_[0]).cross(point_[2] - point_[1]);
    for (int i = 2; i < n_; i++) {
        BigPointType ncr = (point_[i] - point_[i - 1]).cross(point_[i + 1] - point_[i]);
        if (!EQ(cr, ncr)) {
            return false;
        }
    }
    return true;
}


Polygon P, Pre, Res;


int main() {
    int t;
    int n;
    scanf("%d", &t);

    while (t--) {
        P.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            Point2D pt;
            pt.read(i);
            P.addPoint(pt);
        }
        P.grahamScan(false, Res);
        bool flag = true;
        if (Res.size() != n) {
            flag = false;
        }
        else {
            flag = Res.check(t);
        }
        printf("%s\n", flag ? "YES" : "NO");
    }

    return 0;
}

/*
12
0 0
0 0
2 0
4 0
-4 2
-2 2
0 2
2 2
4 2
3 3
2 4
4 4

6
0 0
1 0
2 0
2 1
2 2
1 1

5
0 0
1 0
2 0
2 1
2 2

10
1 2 8
8 3
4 5
6 4
4 3
3 1
2 3
0 4
2 5

10
1 2 6
3 1
4 3
6 4
4 5
3 7
0 4

*/