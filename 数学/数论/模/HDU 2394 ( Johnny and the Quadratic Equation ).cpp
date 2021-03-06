#include <iostream>

using namespace std;

__int64 a, b, c, d, rt[6];
__int64 f[56];

__int64 gcd(__int64 a, __int64 b){

    __int64 m = 1;
    if(a == 0) return b;
    if(b == 0) return a;


    while(m)
    {
        m = a % b;
        a = b;
        b = m;
    }
    return a;

}
int main()
{
    int i;

    f[0] = 1;

    for(i = 1; i <= 32; i++)
        f[i] = f[i-1] * 2;

    int t;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d %I64d %I64d", &a, &b, &c);

        d = f[32];

        rt[0] = gcd(a, b);
        rt[1] = gcd(c, d);
        rt[2] = gcd(rt[0], rt[1]);

        a /= rt[2];
        b /= rt[2];
        c /= rt[2];

        if(a % 2 == 0)
        {
            if(b % 2 == 0)
            {
                if(c % 2 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            }else
                printf("YES\n");
        }else
        {
            if(b % 2)
            {
                if(c % 2)
                    puts("NO");
                else 
                    puts("YES");
            }else
            {
                __int64 rt = (b/2)*(b/2) - a*c;

                while(rt % 4 == 0)
                    rt /= 4;

                if( (rt - 1) % 8 == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
        }
    }
    return 0;
}

