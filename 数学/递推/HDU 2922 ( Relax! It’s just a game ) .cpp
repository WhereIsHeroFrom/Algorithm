#include <iostream>

using namespace std;


int f[100][100], a, b, i, j;

int main()
{
    for(i = 0; i <= 10; i++)
    {
        for(j = 0; j <= 10; j++)
        {
            if(i == 0 || j == 0)
                f[i][j] = 1;
            else
            {
                f[i][j] = f[i-1][j] + f[i][j-1];
            }
        }
    
    }
    while(scanf("%d %d", &a, &b) != EOF && (a!=-1||b!=-1))
        printf("%d+%d%s%d\n", a, b, (a+b==f[a][b])?"=":"!=", a+b );
}
