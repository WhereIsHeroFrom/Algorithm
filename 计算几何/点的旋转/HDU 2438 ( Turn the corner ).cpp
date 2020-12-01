#include <iostream>
#include <cmath>
using namespace std;
#define  pi acos(-1.0)
double i, x, y, l, d;
int flag;
int main()
{
    while(scanf("%lf %lf %lf %lf", &x, &y, &l, &d) != EOF)
    {
        flag = 0;
        if(d > x)
        {
            printf("no\n");
        }else
        {
            for(i = 0.00022; i <= pi / 2; i += 0.00022)
            {
                double rt = d / sin(i) + l * cos(i);

                if ( (rt - y) / rt * ( d / cos(i) + l * sin(i) ) > x )
                {
                     flag = 1;
                     break;
                }
            }
            if(flag)
                printf("no\n");
            else
                printf("yes\n");
        }
    }
}
