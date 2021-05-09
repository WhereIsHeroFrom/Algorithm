#include <iostream>
#include <cmath>
using namespace std;
__int64 power(__int64 x,__int64 n,__int64 p)
{
    __int64 c=0;
    if(n==0)return 1;
    c=power((x*x)%p,n/2,p);
    if(n%2!=0) 
       c=(c*x)%p;
    return c;
}  
__int64 isPrimeNum(__int64 num)
{
    __int64 iSqrt = sqrt(1.0*num);
    __int64 i;
     if (num<2)
         return 0;
     if (num==2)
         return 1;
     if (num % 2 == 0)
         return 0;
     
     for (i=3; i <= iSqrt; i+=2)
     {
         if (num % i == 0)
         {
             return 0;
         }
     }
     return 1;
}
__int64 p,a;
int main()
{
    while(scanf("%I64d %I64d",&p,&a)!=EOF)
    {
        if(p==0&&a==0)break;
        if(power(a,p,p)==a&&isPrimeNum(p)==0)
        {
            printf("yes\n");
        }else printf("no\n");
    }
}
