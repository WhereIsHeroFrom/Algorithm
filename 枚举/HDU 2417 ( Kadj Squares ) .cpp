#include <iostream>
#include <cmath>
using namespace std;
struct point
{
    double start;
    double end;
}temp, tt;

int n, i, j, k, u;
int a[100];
int hash[100];
int sta[100];
int top;
double ty, Max, rt, b[100];
double q1, q2;
int main()
{
    while(scanf("%d", &n) != EOF && n)
    {
        memset(hash, 0, sizeof(hash));
        for(i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        b[1] = a[1];


        memset(hash, 0, sizeof(hash));

        for(i = 2; i <= n; i++)
        {
            b[i] = 0;
            for(j = 1; j < i; j++)
            {
                int ty = b[j] + (a[i] < a[j] ? a[i] : a[j]) * 2;
                if(ty > b[i-1] && ty > b[i])
                {
                    b[i] = ty;
                }
            }

        }


        for(i = 1; i <= n; i++) 
        {        
            temp.start = b[i] - a[i];
            temp.end = b[i] + a[i];
            //printf("%lf %lf %lf\n", b[i], temp.start, temp.end);
            for(j = 1; j <= n; j++)
            {
                if(i == j) continue;
                if(a[i] < a[j])
                {      
                    tt.start = b[j] - a[j];
                    tt.end = b[j] + a[j];
                    //printf("%lf %lf %lf\n", b[i], temp.start, temp.end);
                    if(  ( temp.start > tt.start || fabs(temp.start - tt.start) < 1e-11  )
                        && ( temp.end < tt.end || fabs(temp.end - tt.end) < 1e-11) )
                        break;
                    if(temp.end <= tt.start || temp.start >= tt.end)
                        continue;

                    if(temp.end >= tt.start && tt.start >= temp.start)
                    {
                        temp.end = tt.start;
                    }

                    if(tt.start <= temp.start && temp.start <= tt.end)
                    {
                        temp.start = tt.end;
                    }
                }
            }
            if(j <= n)
                hash[i] = 1;
        }

        top = 0;
        for(i = 1; i <= n ;i++)
        {
            if(!hash[i])
            {
                sta[top++] = i;
            }
        }

        printf("%d", sta[0]);

        for(i = 1; i < top; i++)
            printf(" %d", sta[i]);
        puts("");
    }
}
