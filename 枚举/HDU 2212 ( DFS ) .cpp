#include <iostream>

using namespace std;

int f[100];
int vrt(int u)
{
    int sum = 0;
    while(u)
    {
        sum += f[u%10];
        u /= 10;
    }
    return sum;
}
int main()
{
    int i;
    f[0] = 1;
    for(i = 1; i <= 9; i++)
        f[i] = f[i-1] * i;

    for(i = 1; i <= 50000; i++)
    {
        if(vrt(i) == i)
            printf("%d\n", i);
    }
}
