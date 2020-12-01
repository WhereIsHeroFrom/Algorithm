/*
01背包
概率无法映射到下标，所以这里 
容量 和 价值 互相转化
 
*/
#include <iostream>

using namespace std;

#define MAXN 110
#define MAXV 10010
struct Pack {
    int volume;
    double p;
    
}pack[ MAXN ];

double Max(double a, double b) {
    return a > b ? a : b;
}
double p, f[MAXV];
int n;

int main() {
    int i, j;
    int t;
    scanf("%d", &t);
    
    while( t-- ) {
        scanf("%lf %d", &p, &n);
        int V = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %lf", &pack[i].volume, &pack[i].p);
            pack[i].p = 1 - pack[i].p;
            V += pack[i].volume;
        }
        for(j = 0; j <= V; j++) {
            f[j] = j==0?1:0;
        }
         
        for(i = 0; i < n; i++) {
            for(j = V; j >= pack[i].volume; j --) {
                f[j] = Max(f[j], f[j - pack[i].volume] * pack[i].p);
            }
        }
        /*for(i = 0; i <= V; i++) {
            printf("%d %lf\n", i, f[i]);
        }*/
        
        for(i = V; i >= 0; i--) {
            if(1-f[i] < p) {
                break;
            }
        }
        printf("%d\n", i);
        
    }
    return 0;
}

