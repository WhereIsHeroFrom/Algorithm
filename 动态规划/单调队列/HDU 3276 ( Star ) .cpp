#include <iostream>

using namespace std;

#define MAXN 50010

int N, X, Y;

template <class T>
void swapList(int n, T* arr) {
    int i;
    for(i = 1; i <= n/2; ++i) {
        T v = arr[i];
        arr[i] = arr[n-i+1];
        arr[n-i+1] = v;
    }
}

int a[MAXN];
double sum[MAXN], d[MAXN];
double dp[2][MAXN];
double predp[2][MAXN];

int deq[MAXN], head, tail;

void calcSum() {
    int i;
    for(i = 1; i <= N; ++i) {
        sum[i] = sum[i-1] + d[i];
    }
}

#define INF -10000000000000000.0

double Max(double a, double b) {
    return a > b ? a : b;
}

bool calcDp(double *opt, double *preopt, bool needCheck) {
    head = tail = 0;
    int i;
    preopt[0] = INF;
    for(i = 1; i <= N; ++i) {
        if(i-X >= 0) {
            while(head < tail && sum[i-X] <= sum[ deq[tail-1] ])
                --tail;
            deq[tail++] = i - X;
        }
        while(head < tail && i - deq[head] > Y)
            ++head;

        if(head < tail) {
            opt[i] = sum[i] - sum[ deq[head] ];
        }else {
            opt[i] = INF;
        }
        preopt[i] = Max(preopt[i-1], opt[i]);

        if(needCheck) {
            if(N-i-1 >= 1 && opt[i] + predp[0][N-i-1] >= 0) {
                return true;
            }
        }    
    }
    return false;
}

bool solve(double ave) {
    int i;
    for(i = 1; i <= N; ++i) {
        d[i] = (a[i] - ave);
    }
    calcSum();
    calcDp(dp[0], predp[0], false);

    swapList(N, d);
    calcSum();
    return calcDp(dp[1], predp[1], true);
}

int main() {
    int i;
    int cases = 0;
    while(scanf("%d %d %d", &N, &X, &Y) != EOF) {
        for(i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }
        double l = 0, r = 200000;
        while(r - l > 1e-5) {
            double m = (l + r) / 2;
            if(solve(m)) {
                l = m;
            }else {
                r = m;
            }
        }
        printf("Case %d: %.3lf\n", ++cases, l);
    }
    return 0;
}
