/*
    浮点数精度误差还是很大的，如果能用整数尽量还是整数；
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define INT_POINT


const int MAXP = 2010;
const double eps = 1e-10;
#define NINT_POINT


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
    Point2D operator - (const Point2D& pt) const;
    bool operator < (const Point2D& pt) const;
    BigPointType cross(const Point2D& pt) const;
    BigPointType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
    PointType x() const;
    PointType y() const;
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

BigPointType Vector2D::cross(const Vector2D& pt) const {
    return (BigPointType)x_ * pt.y_ - (BigPointType)y_ * pt.x_;
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}

bool Point2D::operator<(const Point2D& pt) const {
    // 1. 第一关键字： y 小的
    // 2. 第二关键字： x 小的
    // 3. 第三关键字：下标小的 - 适用于重复点
    if (!EQ(y_, pt.y_)) {
        return ST(y_, pt.y_);
    }
    if (!EQ(x_, pt.x_)) {
        return ST(x_, pt.x_);
    }
    return index_ < pt.index_;
}


BigPointType Point2D::distSquare(const Point2D& pt) const {
    Point2D t = *this - pt;
    return SQR(t.x_) + SQR(t.y_);
}

bool Point2D::angleCmp(const Point2D& a, const Point2D& b) {
    if (fabs(a.angle_ - b.angle_) > eps) {
        return a.angle_ < b.angle_;
    }
    if (fabs(a.distSqr_ - b.distSqr_) > eps) {
        return a.distSqr_ < b.distSqr_;
    }
    return a.index_ < b.index_;
}

void Point2D::calculateAngle(const Point2D& o) {
    Point2D t = *this - o;
    if (t.zero()) {
        // 该情况下 atan2 是 undefined 的，需要单独处理
        angle_ = 0;
        distSqr_ = 0;
    }
    else {
        angle_ = atan2(0.0 + t.y_, 0.0 + t.x_); // 这里 y >= 0 是能保证的，所以值在 [0, PI) 之间
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

PointType Point2D::x() const {
    return x_;
}

PointType Point2D::y() const {
    return y_;
}

double Point2D::getAngle() const {
    return angle_;
}

int Point2D::getIndex() const {
    return index_;
}


const int MAXN = 1010;
Point2D P[MAXN], Q[MAXN];


/*
    题意：给定 n(n <= 1000) 个点，求有多少个三元组（无序组）满足三点共线；

    题解：
    1）对于每个点 P，作为最左下角点，其它点如果满足大于它的，加入到集合 S 中；
    2）对集合 S 按照点 P 进行极角排序；
    3）极角原点 P 必选，再根据极角顺序选择两个共线点，假设有 x 个点和原点共线  C(x,2)
*/

int main() {
    int t;
    int n;
    scanf("%d", &t);

    while (t--) {

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            P[i].read(i);
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int s = 0;
            for (int j = 1; j <= n; ++j) {
                if (j==i || P[j] < P[i]) continue;

                Q[s] = P[j];
                Q[s].calculateAngle(P[i]);
                ++s;
            }
            sort(Q, Q + s, Point2D::angleCmp);
            int start = 0;
            int ans1 = 0;
            for (int j = 0; j <= s; ++j) {
                if (j == s || (Q[j]-P[i]).cross(Q[start]-P[i]) != 0 ) {    
                    // 浮点数精度误差还是很大的，如果能用整数尽量还是整数；
                    int cnt = j - start;
                    ans1 += cnt * (cnt-1) / 2;
                    start = j;
                }
            }
            //printf("%d %d %d %d\n", P[i].x(), P[i].y(), s, ans1);
            ans += ans1;
        }

        printf("%d\n", ans);
    }
    return 0;
}

/*
8
0 0 
1 1
2 0
2 2
0 2
3 3
2 3
0 3

9
0 0 
1 0
2 0
0 1
1 1
2 1
0 2
1 2
2 2

9
0 0
-1000000000 0
1000000000 0
-1000000000 1000000000
-1000000000 -1000000000
0 1000000000
0 -1000000000
1000000000 1000000000
1000000000 -1000000000

9
0 0
2 2
4 4
-2 -2 
-4 -4
2 -4
2 4
-2 -4
-2 4
16

16
0 0
1 0
2 0
3 0
0 1
1 1
2 1
3 1
0 2
1 2
2 2
3 2
0 3
1 3
2 3
3 3
*/