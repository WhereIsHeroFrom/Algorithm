#include <iostream>

using namespace std;
int dir[2] = {-1, 1};
int s;
int main()
{
    int t, i, sum;
    scanf("%d", &t);
    while(t--)
    {
        sum  = 0;
        for(i = 0; i < 6; i++)
        {
            scanf("%d", &s);
            sum += dir[(i+1)%2] * s;
        }
        if(sum)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
