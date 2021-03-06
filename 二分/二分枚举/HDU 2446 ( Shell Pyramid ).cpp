#include <iostream>

using namespace std;

__int64 pre(__int64 u)
{
/*    if(u == 0)
    {
        while(1)
        {

        }
    }*/


    if(u % 3 == 0)
    {
         __int64 rt = u / 3;
         
         if(u % 2 == 0)
         {
             return (u / 2 + 1) * rt * (u + 1);
         }else
         {
             return (u + 1) / 2 * rt * (u + 2);
         }
    }else if(u % 3 == 1)
    {
        __int64 rt = (u + 2) / 3;

         if(u % 2 == 0)
         {
             return (u / 2) * rt * (u + 1);
         }else
         {
             return (u + 1) / 2 * rt * (u);
         }
    }else
    {
        __int64 rt = (u + 1) / 3;

        if(rt % 2 == 0)
            return rt / 2 * u * (u + 2);
        else
            return u / 2 * (u + 2) * rt;
    }
}

__int64 ya(__int64 ty)
{
    if(ty % 2 == 0)
        return ty / 2 * (ty + 1);
    return (ty + 1) / 2 * ty;

}
__int64 s, lef, rig;
__int64 i;
__int64 low, high, mid;

int main()
{

    int t;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d", &s);

        if(!s)
        {
            printf("0 0 0\n");
            continue;
        }

        if(s == 1)
        {
            printf("1 1 1\n");
            continue;
        }

        low = 2;
        high = 3810777;
        //printf("%I64d %I64d\n", pre(high), pre(high+1));

        if(s >= pre(high) + 1)
        {
            i = high + 1;
        }else
        {    
            while(low < high)
            {
                mid = (low + high) / 2;

                lef = pre(mid-1) + 1;
                rig = pre(mid);

                if(  lef <= s && s <= rig )
                    break;
                else if(s < lef)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            __int64 op = mid - 11;

            if(op < 2)
                op = 2;

            for(i = op; i < op + 22 && i <= 3810777; i++)
            {    
                lef = pre(i-1) + 1;
                rig = pre(i);
                if(  lef <= s && s <= rig )
                    break;
            }
        }


        printf("%I64d ", i);

        s -= pre(i-1);

        {

            if(s == 1)
            {
                printf("1 1\n");
                continue;
            }

            low = 2;
            high =  i + 10;

            while(low < high)
            {
                mid = (low + high) / 2;
                lef = ya(mid-1) + 1;
                rig = ya(mid);

                if(  lef <= s && s <= rig )
                    break;
                else if(s < lef)
                    high = mid - 1;
                else
                    low = mid + 1;

            }

            __int64 op = mid - 10;

            if(op < 2)
                op = 2;

            for(i = op; i < op + 20; i++)
            {    
                lef = ya(i-1) + 1;
                rig = ya(i);
                if(  lef <= s && s <= rig)
                    break;
            }

            s -= ya(i-1);

            printf("%I64d %I64d\n", i,  s);
        }
    }

}

/*
9223372036854715807
546
9223371416043870028
620810905778
*/
