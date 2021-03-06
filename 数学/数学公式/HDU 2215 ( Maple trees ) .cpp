#include <iostream>
#include <cmath>
using namespace std;
struct point
{
    double x;
    double y;
}p[201];

double dis(point a, point b)
{
    double tp = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    return sqrt(tp);
}

double DunJiao(double a, double b, double c)
{
    return (a*a + b*b - c*c)/2/a/b;
}
double Ban(point a, point b, point c)
{
    double ab = dis(a, b);
    double ac = dis(a,  c);
    double bc = dis(b, c);

    double p = (ab+bc+ac)/2;
    p = sqrt(p*(p-ab)*(p-bc)*(p-ac));

    return ab*bc*ac/4/p;
}
double Is_Dun(point a, point b, point c)
{    
    double ab = dis(a, b);
    double ac = dis(a,  c);
    double bc = dis(b, c);

    double tp;

    if(DunJiao(ab, ac, bc) < 0)
        return bc/2;
    if(DunJiao(ab, bc, ac) < 0)
        return ac/2;
    if(DunJiao(bc, ac, ab) < 0)
        return ab/2;

    tp = -3000;
    return tp;
}
int n, i, j, k;
double Max;
int main()
{
    while(scanf("%d", &n) != EOF && n)
    {
        Max = -1;
        for(i = 0; i < n ; i++)
        {
           scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if(n == 1)
        {
            printf("%.2lf\n", 0.5);
        }else if(n == 2)
        {
            printf("%.2lf\n", dis(p[0], p[1])/2 + 0.5 );
        }else
        {
            for(i = 0; i < n ; i++)
            {
                for(j = i+1; j < n ; j++)
                {
                    for(k = j+1; k < n ; k++)
                    {
                        double tp = Is_Dun(p[i], p[j], p[k]);
                        if(tp < -2000)
                        {
                            double zjt = Ban(p[i], p[j], p[k]);
                            if(zjt > Max)
                                Max = zjt;
                        }
                        else
                        {
                            if(tp > Max)
                                Max = tp;
                        }
                    }
                }
            }
            printf("%.2lf\n", Max + 0.5);
        }
    
    }
}
