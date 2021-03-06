#include <iostream>
#include <cmath>
using namespace std;
__int64 M;
__int64 f[1000], p[1000];

__int64 RongChi(__int64 e, __int64 v)
{


    __int64 b, i, top, j;
    __int64 buf[20], zong = 0;
    __int64 s = 1 << v;

    for(i = 1; i < s; i++)
    {
        b = i;
        top = 0;
        while(b)
        {
            buf[ top ++] = b%2;
            b = b >> 1;
        }
        for(j = top; j < v; j++)
        {
            buf[j] = 0;
        }
        top = v;

        __int64 sum = 1, coun = 0;

        for(j = top - 1; j >= 0; j--)
        {
            if(buf[j])
            {
                coun ++;
                sum *= p[j];
            }
        }        
        if(coun & 1)
            zong += (__int64)(pow(e, 1.0/sum) - 1);
        else
            zong -= (__int64)(pow(e, 1.0/sum) - 1);
    }
    return zong;

}
int main()
{
    
    __int64 i, j, k = 0, n;
    for(i = 2; i <= 59; i ++)
    {
        if(!f[i])
        {
            p[k++] = i;
            for(j = i+i; j <= 59; j += i)
            {
                f[j] = 1;
            }
        }
    }
    while(scanf("%I64d", &n)!= EOF)
    {
        if(n == 1)
            printf("1\n");
        else
        {
            for(i = 0; i < k; i++)
            {
                if(pow(1.0*n, 1.0/p[i]) < 2)
                    break;
            }
            printf("%I64d\n", RongChi(n, i + 1) + 1);
        }
    }
}
