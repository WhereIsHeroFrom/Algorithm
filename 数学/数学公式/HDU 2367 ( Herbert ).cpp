#include <iostream>

using namespace std;
unsigned __int64 n;
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d", &n);
        if(n == 0)
            printf("1\n");
        else if(n == 1)
            printf("2\n");
        else
            printf("%I64u\n", (n-2)*(n-2) + n*n + 1);
    }
}
