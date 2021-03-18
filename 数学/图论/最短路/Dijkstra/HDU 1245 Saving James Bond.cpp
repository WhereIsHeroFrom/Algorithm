#include <iostream>
#include <cmath>
using namespace std;

struct point {
    int x;
    int y;
}p[110];

int n;
double limit;
double dis[110][110], map[110][110];
int flag[110][110];
int step;

double Dis(point a, point b) {
    return sqrt(1.0 * (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double Min(double a, double b) {
    return a < b ? a : b;
}

double MIN;

int main() {

    int i, j, k;
    while (scanf("%d %lf", &n, &limit) != EOF) {
        for (i = 0; i < n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                map[i][j] = dis[i][j] = Dis(p[i], p[j]);
                if (map[i][j] > limit)
                    map[i][j] = INT_MAX;
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {

                if (map[i][j] > limit) {
                    flag[i][j] = 10000000;
                    continue;
                }

                if (i == j)
                    flag[i][j] = 0;
                else
                    flag[i][j] = 1;
            }
        }

        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++) {
                if (flag[i][k] == 10000000)
                    continue;
                for (j = 0; j < n; j++) {
                    if (flag[k][j] == 10000000)
                        continue;

                    if (map[i][k] + map[k][j] < map[i][j]) {
                        map[i][j] = map[i][k] + map[k][j];
                        flag[i][j] = flag[i][k] + flag[k][j];
                    }
                    else if (map[i][k] + map[k][j] == map[i][j]) {
                        if (flag[i][k] + flag[k][j] < flag[i][j])
                            flag[i][j] = flag[i][k] + flag[k][j];
                    }
                }
            }
        }

        MIN = INT_MAX;

        for (i = 0; i < n; i++) {

            double del1 = sqrt(1.0*p[i].x*p[i].x + p[i].y*p[i].y) - 7.5;
            if (del1 > limit)
                continue;

            for (j = 0; j < n; j++) {

                double sum = map[i][j];

                if (flag[i][j] == 10000000)
                    continue;

                double x = Min(50.0 - p[j].x, 50.0 - p[j].y);
                double y = Min(p[j].x + 50.0, p[j].y + 50.0);

                double del2 = Min(x, y);
                if (del2 > limit)
                    continue;

                sum += (del1 + del2);
                int now = flag[i][j];

                if (p[j].x == 50 || p[j].x == -50 || p[j].y == 50 || p[j].y == -50) {
                }
                else
                    now++;

                if (sqrt(p[i].x*p[i].x + p[i].y*p[i].y*1.0) <= 7.5){
                }
                else
                    now++;

                if (sum < MIN) {
                    MIN = sum;
                    step = now;
                }
                else if (sum == MIN) {
                    if (now < step)
                        step = now;
                }
            }
        }

        if (MIN >= INT_MAX - 1)
            printf("can't be saved\n");
        else
            printf("%.2lf %d\n", MIN, step);

    }
    return 0;
}