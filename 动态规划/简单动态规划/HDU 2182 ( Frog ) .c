#include <stdio.h>
int v[200], n, a, b, k, i, j, e, t, Max;
int h[120][120];
int main()
{
    scanf("%d", &t);
    while(t --)
    {
        scanf("%d%d%d%d", &n, &a, &b, &k);
        for(i=0;i<n;i++)
        {
            scanf("%d", &v[i]);
        }
        for(i = 0;i < 120; i++)
        {
            for(j = 0;j < 120;j++)
            {
                h[i][j] = -99999999;
            }
        }
        h[0][0] = v[0];
        if(k > n)
           k = n + 2;
        for(i = 1; i <= k; i++)
        {
            for(j=0;j<n;j++)
            {
                Max = -1;
                for(e = a;e <= b; e ++)
                {
                    if(j - e < 0)
                        break;
                    if(h[i - 1][j - e] + v[j] > Max)
                    {
                        Max =  h[i - 1][j - e] + v[j];
                    }
                }
                if(Max != -1)
                {
                    h[i][j] = Max;
                }
            }
        }Max = -1;
        for(;k>=0;k--)
        {
          for(i=0;i<n;i++)
             if(h[k][i] > Max)
              Max = h[k][i];
        }
        printf("%d\n", Max);
     }
}
