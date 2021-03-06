#include <iostream>
using namespace std;
__int64 c[1001][1001];
int main()
{
    int i, j;
    c[0][0] = 1;
    for(i = 1; i <= 1000; i++)
    {
        for(j = 0; j <= i; j++)
        {
            if(j == 0 || j == i)
                c[i][j] = 1;
            else
                c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
    __int64 n;
    while(scanf("%I64d", &n) != EOF)
    {
        __int64 sum = 0;
        for(i = 2; i <= n; i++)
        {
            sum += c[n][i] * ( i - 1);
        }
        printf("%I64d\n", sum);

    }
}
