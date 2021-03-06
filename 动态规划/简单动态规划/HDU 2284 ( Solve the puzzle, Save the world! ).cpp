#include <iostream>
using namespace std;

int p;
int dp[100001];

int c(int n)
{
    int sum = 0;
    int t = p;
    while(n / t)
    {
        sum += n/t;
        t *= p;
    }
    return sum;
}

int main()
{
    int n, i;

    while(scanf("%d %d", &n, &p) != EOF)
    {
        memset(dp, -1, sizeof(dp) );

        int coun = 0;

        for(i = 0; i <= n; i++) {

            if(dp[n] == -1)
                dp[n] = c(n);

            if(dp[n-i] == -1)
                dp[n-i] = c(n-i);

            if(dp[i] == -1)
                dp[i] = c(i);

            if( dp[n] > dp[n-i] + dp[i] ) {
                coun ++;
            }
        }
        if(!coun)
            printf("Where is hero from?\n");
        else
            printf("%d\n", coun);
    }
}


