#include <iostream>
using namespace std;

__int64 ty, n, x, i, f[100], buf[100];
main()
{
    f[0] = 1;
    for(i = 1; i <= 40; i++)
    {
        f[i] = f[i-1]*2;
        
    }
    for(i = 1; i <= 40; i++)
    {
        f[i] -= (__int64)1;
        //printf("%I64d\n", f[i]);
    }

    while(scanf("%I64d", &n) != EOF)
    {
        for(i = 0;;i++)
        {
            if(n + 1 <= f[i] - 1)
                break;
        }
        __int64 tp = f[32] - f[i];

        __int64 A;
        int k = 0;
        while(tp)
        {
            buf[k++] = tp % 256;
            tp /= 256;
        }
        if(k == 4)
           printf("%I64d.%I64d.%I64d.%I64d\n", buf[3], buf[2], buf[1], buf[0]);
        else if(k == 3)
           printf("%I64d.%I64d.%I64d.%I64d\n", buf[2], buf[1], buf[0], 0);
        else if(k == 2)
           printf("%I64d.%I64d.%I64d.%I64d\n", buf[1], buf[0], 0, 0);
        else if(k == 1)
           printf("%I64d.%I64d.%I64d.%I64d\n", buf[0], 0, 0, 0);
        else
           printf("%I64d.%I64d.%I64d.%I64d\n", 0, 0, 0, 0);

    }
}
