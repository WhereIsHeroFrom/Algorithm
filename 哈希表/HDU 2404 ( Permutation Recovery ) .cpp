#include <iostream>

using namespace std;

int hash[10000];
int a[10000];
int n, i, j, coun;
int main()
{
    while(scanf("%d", &n) != EOF && n)
    {
        memset(hash, 0, sizeof(hash));

        for(i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        hash[ a[1] + 1 ] = 1;

        for(i = 2; i <= n; i++)
        {
            coun = 0;
            for(j = 1; j <= n; j++)
            {
                if(!hash[j])
                    coun ++;

                if(coun == a[i] + 1)
                    break;
            }
            hash[j] = i;
        }

        for(i = 1; i <= n; i++)
        {
            if(i != 1)
                printf(",");
            printf("%d", hash[i]);
        }
        puts("");

    }
}
