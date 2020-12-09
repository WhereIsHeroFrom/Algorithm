#include <iostream>
#include <cmath>
using namespace std;
int x[670002];

int num[670002]; //包含
int a, Max, n, i, j, t, ty;
int main()
{
    while(scanf("%d%d", &n, &t) != EOF)
    {
        memset(x, 0, sizeof(x));
        memset(num, 0, sizeof(num));

        for(i = 0; i < n ;i++)
        {
            scanf("%d", &a);
            x[ a + 300000] ++;
        }
        ty = x[300000];
        x[300000] = 0;

        for(i = 300000 - 1; i >= 0; i--)
        {
            if(x[i])
                num[i] = num[i+1] + x[i];
            else
                num[i] = num[i+1];
        }

        for(i = 300000 + 1; i <= 600000; i++)
        {
            if(x[i])
                num[i] = num[i-1] + x[i];
            else
                num[i] = num[i-1];
        }

        Max = 0;

        int tp;

        for(i = 0; i <= t; i++)
        {
            if(t - 2*i >= 0)
            {
                tp = num[300000 + i] + num[300000 - (t - 2*i)];
                if(tp > Max)
                {
                    Max = tp;
                }
            }
        }

        for(i = 0; i <= t; i++)
        {
            if(t - 2*i >= 0)
            {
                tp = num[300000 - i] + num[300000 + (t - 2*i)];
                if(tp > Max)
                {
                    Max = tp;
                   
                }
            }
        }

        if(num[300000 + t] > Max)
            Max = num[300000 + t];

        if(num[300000 - t] > Max)
            Max = num[300000 - t];

        if(ty)
            Max += ty;

        printf("%d\n", Max);


    }
    return 0;
}

