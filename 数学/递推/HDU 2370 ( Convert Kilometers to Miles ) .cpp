#include <iostream>
using namespace std;
int f[100], stack[100], top, hash[22];
int main()
{
    int t, x, i, ty;
    f[1] = 1; f[2] = 2;
    for(i = 3; i <= 21; i++)
        f[i] = f[i-1] + f[i-2];

    scanf("%d", &t);
    while(t--)
    {
        memset(hash, 0, sizeof(hash));
        scanf("%d", &ty); top = 0; i = 21;
        int sum = 0;
        while(1)
        {
            if(ty == 0) break;
            if(ty < f[i])
                i--;
            else if(ty >= f[i] && !hash[i+1])
            {
                sum += f[i-1];
                ty -= f[i];
            }
        }
        printf("%d\n", sum);
    }
}
