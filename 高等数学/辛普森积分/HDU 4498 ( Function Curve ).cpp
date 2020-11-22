#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#pragma comment(linker, "/STACK:1024000000,1024000000") 
#define EPS 1e-6
#define INF -12345678.0

double sqr(double x) {
    return x*x;
}

struct KAB {
    double k, a, b;
    double A, B, C;
    void read() {
        int _K, _A, _B;
        scanf("%d %d %d", &_K, &_A, &_B);
        k = _K;
        a = _A;
        b = _B;
    }
    double f(double x) {
        x -= a;
        x *= x;
        return k*x+b;
    }
    
    double F(double x) {
        return sqrt( sqr(2*k*x - 2*a*k) + 1 );
    }
    
    void get_root(double l, double r, double ansx[2]) {
        double delt = B*B-4*A*C;
        if(fabs(delt) < EPS) delt = 0;
        if(delt < 0) {
            return ;
        }
        delt = sqrt(delt);
        double x1, x2;
        x1 = (-B + delt) / 2 / A;
        x2 = (-B - delt) / 2 / A;
        if(l <= x1 && x1 <= r) ansx[0] = x1;
        if(l <= x2 && x2 <= r) ansx[1] = x2;    
    }
    
    void crossWithLine(double l, double r, double ansx[2]) {
        A = k;
        B = -2*a*k;
        C = a*a*k + b - 100;
        ansx[0] = ansx[1] = INF;
        get_root(l, r, ansx);
    }
    
    double crossWithPro(const KAB &other, double l, double r, double ansx[2]) {
        A = k - other.k;
        B = - 2*a*k + 2*other.a*other.k;
        C = a*a*k - other.a*other.a*other.k + b - other.b;
        ansx[0] = ansx[1] = INF;
        get_root(l, r, ansx);
    }
    
}K[52];
int n;

double f(double x, int& idx) {
    idx = -1;
    double min = 100;
    for(int i = 0; i < n; ++i) {
        double v = K[i].f(x);
        if(v < min) {
            min = v;
            idx = i;
        }
    }
    return min;
}

double simpson(int idx, double a, double b) {
    if(idx == -1) {
        return b-a;
    }
    double m = (a + b) / 2;
    return (b-a)/6 * (K[idx].F(a) + 4*K[idx].F(m) + K[idx].F(b) );
}

double get_intergration(int idx, double a, double b, double eps, double s) {
    double m = (a+b)/2;
    double s1 = simpson(idx, a, m);
    double s2 = simpson(idx, m, b);
    if(fabs(s - (s1+s2)) < eps) {
        return s;
    }else {
        return get_intergration(idx, a, m, eps/2, s1) + get_intergration(idx, m, b, eps/2, s2);
    }
}

void get_cross(double l, double r, int idx1, int idx2, double ansx[2]) {
    if(idx1 == -1) {
        K[idx2].crossWithLine(l, r, ansx);
    }else if(idx2 == -1) {
        K[idx1].crossWithLine(l, r, ansx);
    }else
        K[idx1].crossWithPro(K[idx2], l, r, ansx);
}

double X[3010];
int XCount;

void uniqueX() {    
    int m = 1;
    for(int i = 1; i < XCount; ++i) {
        if(fabs(X[i] - X[i-1]) < EPS) {
            continue;
        }
        X[m++] = X[i];
    }
    XCount = m;
}
 
int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; ++i) K[i].read();
        
        XCount = 0;
        X[XCount++] = 0;
        X[XCount++] = 100;
        
        // 计算任意两个抛物线的交点 
        for(i = 0; i < n; ++i) {
            for(j = i+1; j < n; ++j) {
                double ansx[2];
                get_cross(0, 100, i, j, ansx);
                if(ansx[0] >= 0) X[XCount++] = ansx[0];
                if(ansx[1] >= 0) X[XCount++] = ansx[1];
            }
        }
        
        // 计算抛物线和直线的交点
        for(i = 0; i < n; ++i) {
            double ansx[2];
            get_cross(0, 100, i, -1, ansx);
            if(ansx[0] >= 0) X[XCount++] = ansx[0];
            if(ansx[1] >= 0) X[XCount++] = ansx[1];
        } 
        
        sort(X, X+XCount);
        uniqueX();
        double len = 0;
        for(i = 1; i < XCount; ++i) {
            double x = (X[i] + X[i-1]) / 2;
            int idx;
            f(x, idx);
            //printf("%lf %lf\n", X[i-1], X[i]);
            if(idx == -1) {
                len += X[i] - X[i-1];
            }else {
                len += get_intergration(idx, X[i-1], X[i], 1e-3/XCount, simpson(idx, X[i-1], X[i]) );
            }
        }
        
        printf("%.2lf\n", len);
    }
    return 0;
} 
