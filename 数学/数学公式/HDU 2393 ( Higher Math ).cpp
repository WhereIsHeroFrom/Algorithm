#include<iostream>
#include <algorithm>
using namespace std;
__int64 a[3];
int main()
{
    int t;
    int c = 1;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d %I64d %I64d", &a[0], &a[1], &a[2]);
        sort(a, a+3);
        printf("Scenario #%d:\n", c++);
        if(a[0]*a[0] + a[1]*a[1] == a[2]*a[2])
            printf("yes\n");
        else
            printf("no\n");
        puts("");
    }
    return 0;
}

