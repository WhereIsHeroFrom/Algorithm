#include <iostream>
#include <cmath>
using namespace std;

struct point
{
    double x;
    double y;
    double k;
}p[200001];

int m, n;
double Min, yu, x, y;
int main()
{
    int i;
    while(scanf("%d%d", &m, &n) != EOF)
    {
        Min = 2100000000;
        for(i = 0; i < 20000; i++)
            p[i].x = p[i].y = 0;
        for(i = 0; i < m; i++)
        {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if(!n)
        {
            printf("0.000\n");
            continue;
        }
        for(i = 0; i < m; i++)
        {
            if(i == 0)
                continue;

            yu = 1.0*n / p[i].x / p[i].x + p[i].y;

            if(yu < Min)
                Min = yu;

            p[i].k = (p[i].y - p[i-1].y) / (p[i].x - p[i-1].x);

            yu = pow(2*n*1.0 / p[i].k, 1.0/3 + 0.000001);


            if(yu < p[i-1].x)
            {
                yu = p[i].k * p[i-1].x+ p[i].y - p[i].k*p[i].x + 1.0*n / p[i-1].x / p[i-1].x;
                if(yu < Min)
                    Min = yu;
            }else if(yu > p[i].x)
            {
                yu = p[i].k * p[i].x + p[i].y - p[i].k*p[i].x+ 1.0*n / p[i].x / p[i].x;
                if(yu < Min)
                    Min = yu;
            }else
            {
                yu = p[i].k * yu + p[i].y - p[i].k*p[i].x + 1.0*n / yu / yu;
                if(yu < Min)
                    Min = yu;
            }

        }
        printf("%.3lf\n", Min);


    }

}

