// HDU 2080
// 计算几何：点乘 计算夹角
// 注意浮点数精度问题，不要输出 -0.00

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define eps 1e-9

struct Point {
	Point() {

	}
	Point(double _x, double _y) : x(_x), y(_y) {

	}

	void Scanf() {
		scanf("%lf %lf", &x, &y);
	}

	Point operator+(const Point& o) {
		return Point(x + o.x, y + o.y);
	}


	Point operator-(const Point& o) {
		return Point(x - o.x, y - o.y);
	}

	double cross(const Point& o) {
		return x * o.y - y * o.x;
	}

	double operator* (const Point& o) {
		return x*o.x + y*o.y;
	}

	double len() const {
		return sqrt(x*x + y*y);
	}

private:
	double x, y;

}P[1000];

int n;
int main() {

	int i;
	int t;
	scanf("%d", &t);
	while (t--) {
		for (i = 0; i < 2; ++i) {
			P[i].Scanf();
		}
		double s = P[0] * P[1];
		double ans = acos(s / P[0].len() / P[1].len()) * 180 / acos(-1.0);
		if (fabs(ans) < eps) ans = 0;
		printf("%.2lf\n", ans);
	}
	return 0;
}