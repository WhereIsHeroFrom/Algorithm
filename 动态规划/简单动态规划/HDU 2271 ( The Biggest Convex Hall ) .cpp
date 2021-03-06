#include <iostream>
#include <cmath>
using namespace std;

#define pi acos(-1.0)

struct point {
    int x;
    int y;
    double thi;
    int length;
}p[101];

int n, i;
int dp[101][101];

//dot ???0 ????????
int dot(point a, point b, point c) {
    point tp1, tp2;
    tp1.x = a.x - b.x;
    tp1.y = a.y - b.y;

    tp2.x = b.x - c.x;
    tp2.y = b.y - c.y;
    return tp1.x * tp2.y - tp1.y * tp2.x;
}

int cmp(const void *a, const void *b) {
    point *c = (point *)a;
    point *d = (point *)b;
    if(fabs(c->thi - d->thi) < 1e-11){
        return - c->length + d->length;
    }
    return c->thi < d->thi ? 1 : -1;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {

    int i, j, k;
    point tp[3];
    tp[0].x = 0; tp[0].y = 2;
    tp[1].x = 1; tp[1].y = 1;
    tp[2].x = 0; tp[2].y = 0;
    point zero;
    zero.x = zero.y = 0;

    while(scanf("%d", &n) != EOF) {

        for(i = 0; i < n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
            if(p[i].x == 0) {
                p[i].thi = pi / 2;
            }else {
                p[i].thi = atan( p[i].y * 1.0 / p[i].x );
            }
            p[i].length = p[i].x*p[i].x + p[i].y*p[i].y;
        }

        qsort(p, n, sizeof(point), cmp);
        memset(dp, 0, sizeof(dp));

        //for(i = 0; i < n; i++) {
        //    printf("%d %d\n", p[i].x, p[i].y);
        //}

        int Maxi = 0;

        for(i = 0; i < n; i++) {
            for(j = i + 1; j < n; j++) {
                if( !(p[j].y * p[i].x == p[i].y * p[j].x) )
                    dp[i][j] = 3;
                else
                    dp[i][j] = 2;

                if(dp[i][j] > Maxi)
                    Maxi = dp[i][j];
            }
        }

        for(i = 1; i < n; i++) {
            for(j = i + 1; j < n; j++) {

                for(k = 0; k < i; k++) {
                    if(dot(p[k], p[i], p[j]) == 0) {
                        dp[i][j] = Max( dp[i][j], dp[k][i] );
                    }else if( dot(p[k], p[i], p[j]) < 0 ) {
                        dp[i][j] = Max( dp[i][j], dp[k][i] + 1);
                    }
                }

                if(dp[i][j] > Maxi)
                    Maxi = dp[i][j];
            }
        }

        printf("%d\n", Maxi);

    }
    return 0;
}

