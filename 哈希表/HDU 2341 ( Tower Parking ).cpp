#include <iostream>
#include <cmath> 
using namespace std;

int h, l, shou[101][101];
int buf[51];
int hash[10000], a, x, y, t, i, j;
int Min(int a, int b)
{
    return a < b ? a : b;
}
  
int main()
{
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d%d", &h, &l);
        memset(hash, -1, sizeof(hash));
        for(i = 1; i <= h; i++)
        {
            for(j = 1; j <= l; j++)
            {
                scanf("%d", &shou[i][j]);
                if(shou[i][j] != -1)
                    hash[shou[i][j]] = i*100 + j;
            }
        }
        int sum = 0;
        int prex = 1, prey = 1;
        for(i = 1; i <= 2501; i++)
        {
            if(hash[i] == -1)
                continue;
            x = hash[i] / 100;
            y = hash[i] % 100;

            sum += (x-1)*20;

            if((y-1) > l - (y-1))
            {
                sum += (l - (y-1))*5;
            }else
            {
                sum += (y-1)*5;
            }        
            for(j = 1; j <= l; j++)
                 shou[x][l+j] = shou[x][j];

            for(j = 1; j <= l; j++)
            {
                shou[x][j] = shou[x][j+y-1];
                if(shou[x][j] != -1)
                      hash[shou[x][j]] = x*100 + j;
            }

            prex = x;
        }
        printf("%d\n", sum);

    }
}
