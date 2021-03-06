#include <iostream>
#include <cmath>
using namespace std;

struct dp_mul
{
    int pri;
    int next;
}dp1[5001];

struct dp_sum
{
    int pri;
    int next;
}dp2[5001];


void printmul(int u)
{
    if(dp1[u].next == dp1[u].pri)
    {
        int i;
        for(i = 0; i < dp1[u].next; i++)
            printf("|");
    }else
    {
        printmul(dp1[u].next);
        printf("x");
        printmul(u/dp1[u].next);
    }
}

void printsum(int u)
{
    if(dp2[u].next < 0)
    {
        printmul(u);
    }else
    {
        printsum(dp2[u].next);
        printf("+");
        printsum(u-dp2[u].next);
    }

}
int n;

int main()
{
    int i, j;

    for(i = 1; i <= 5000; i++)
    {
        dp1[i].pri = i;
        dp1[i].next = i;

        int yu = sqrt(i*1.0);
        for(j =    1; j <= yu; j++)
        {
            if(i % j == 0)
            {
                if(dp1[i/j].pri + dp1[j].pri + 2 < dp1[i].pri)
                {
                    dp1[i].pri = dp1[i/j].pri + dp1[j].pri + 2;
                    dp1[i].next = j;
                }
            }
        }
    }

    for(i = 1; i <= 5000; i++)
    {
        dp2[i].pri = dp1[i].pri;
        dp2[i].next = -999999;

        for(j = 1; j < i / 2; j++)
        {
            if(dp2[i-j].pri + dp2[j].pri + 2 < dp2[i].pri)
            {
                dp2[i].pri = dp2[i-j].pri + dp2[j].pri + 2;
                dp2[i].next = j;
            }
        }
    }

    while(scanf("%d", &n) != EOF)
    {
        printf("%d toothpicks: ", dp2[n].pri);
        printsum(n);
        printf("=%d\n", n);
    }
    
}

