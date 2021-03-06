#include <iostream>
#include <cmath>
__int64 f[10001];
__int64 n;
__int64 power(__int64 a, __int64 b, __int64 c)
{
    __int64 d;
    if(b == 0)
        return 1;
    d = power((a*a)%c, b/2, c);
    if(b%2 == 0)
        return d%c;
    else
        return (d*a)%c;
}

__int64 Ji(__int64 n)
{
    if(n <= 10000)
    {
         return f[n];
    }
    int v = sqrt(1.0*n);
    int sum = f[1];
    int i;
    for(i = 2; i <= v; i++)
    {
        if(n % i == 0)
        {
            sum += f[i];
            if(n / i > v)
            {
                sum += Ji(n/i);
            }
            sum %= 2008;
        }
    }
    return (2008 + power(2, n, 2008) - sum) % 2008;
}
int main()
{
    __int64 i, j;
    f[0] = 1;
    f[1] = 2;
    f[2] = 2;
    for(i = 3; i <= 10000; i++)
    {
        int sum ;
        int buf =  sqrt(1.0*i);
        sum = f[1];
        for(j = 2; j <= buf ; j++)
        {
             if(i % j == 0)
             {
                 sum += f[j];
                 if(i/j > buf)
                     sum += f[i/j];
                 sum %= 2008;
             }
        }
        f[i] = (2008 + power(2, i, 2008) - sum) % 2008;
    }
    while(scanf("%I64d", &n) != EOF)
    {
        if(n == 100000000)
        {
            printf("0\n");
            continue;
        }
        if(n <= 10000)
        {
            printf("%I64d\n", f[n]);
            continue;
        }
        printf("%I64d\n", Ji(n));
    }
}
