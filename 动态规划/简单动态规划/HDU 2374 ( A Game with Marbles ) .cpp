#include <iostream>

using namespace std;

__int64 a[10000];
__int64 i, j, n, sum;
int main()
{
    while(scanf("%I64d", &n) != EOF && n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%I64d", &a[i]);
        }
        sum = 0;
        for(i = n-1; i >= 0; i --)
        {
            for(j = 0; j < i; j++)
            {
                a[j] += a[i];
            }
            sum += a[i];
        }
        printf("%I64d\n", sum);
    }
}
