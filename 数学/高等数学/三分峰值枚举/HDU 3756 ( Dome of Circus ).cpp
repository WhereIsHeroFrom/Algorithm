/*
题意：
    在一个三维空间中，给定一些点，这些点的z坐标都是大于0的。要求求
出一个圆锥（底面是圆形），使得这个圆锥的底面在z = 0的平面上，它能够
包含所有给定的点并且圆锥的体积要求最小。

题解：
    数学推导 + 二分

思路：
    这是一个很有意思的题，虽然是三维的，但是可以很容易的转化到二维去
。来看X-Z这个平面，我们将所有的点进行圆周映射，然后将所有的点都投影到
X-Z平面的的第一象限去，然后问题就转化成了在X-Z平面上找到一条斜率为负
的直线L，L和X正方向、Z正方向围成的三角形包含所有点，如果假设L和X轴的
交点为R，和Z轴焦点为H，要求pi*H*R^2的值最小。
    然后我们来看看H和R之间有什么千丝万缕的关系。首先L这条线必定和某一
个给定的点擦边，也就是经过那个点，我们假设它经过P(a, b)， 并且L的斜率
为K(K < 0)，那么L的方程就可以表示为 L:  y = K * (x - a) + b，则H和R就
可以利用这个方程表示出来：
H = -a * K + b;
R = -b / K + a;
那么所求的圆锥的体积就是：
V = pi*H*R^2 = pi * (-a * K + b) * (-b / K + a) ^ 2
容易得到V(K)这个函数的导数：
V'(K) = - pi * (aK^2 + 2bK) * (aK - b)^2 / K^2
影响这个导数的正负性的唯一条件是 -(aK^2 + 2bK)
当-2b/a < K < 0时V'(K)大于零，也就是V的值是随着K递增的。
当K < -2b/a时V'(K)小于零，也就是V的值是随着K递减的。
于是可以得出一个结论，当K = -2b/a 时V取得最小值。
于是我们知道了V的单峰性，然后可以通过枚举
*/

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-6
const double pi = acos(-1.0);

struct Point {
    double x, y, z;
    double v, h;

    void SCANF() {
        scanf("%lf %lf %lf", &x, &y, &z);
        v = z;
        h = sqrt(x*x + y*y);
    }
}pt[ 10001 ];

int n;
double MaxH, MaxV;

double Calc(double R) {
    int i;
    double Max = 0;
    int idx = 0;
    for(i = 0; i < n; i++) {
        double nv = pt[i].v / (R - pt[i].h);
        if(nv > Max) {
            Max = nv;
            idx = i;
        }
    }
    return Max * R;
}

int main() {
    int t;
    int i;

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        MaxH = MaxV = 0;
        for(i = 0; i < n; i++) {
            pt[i].SCANF();
            if(pt[i].h > MaxH)
                MaxH = pt[i].h;
            if(pt[i].v > MaxV)
                MaxV = pt[i].v;
        }

        double l = MaxH + eps, r = 1e6;
        double ml, mr;

        while(l + 1e-8 < r) {
            ml = (2 * l + r) / 3;
            mr = (l + 2 * r) / 3;

            double lans = Calc(ml) * ml * ml;
            double rans = Calc(mr) * mr * mr;

            if( lans > rans ) {
                l = ml + 1e-7;
            }else
                r = mr - 1e-7;
        }
        double ans = (l + r) / 2;
        printf("%.3lf %.3lf\n", Calc(ans), ans);
    }
    return 0;
}
