#include <iostream>

using namespace std;

int g[100001];
int no[100001];
int n, m, i, j;
int hash[100001];
int sum, u, rt;
int main()
{
    while(scanf("%d %d", &n, &m) != EOF)
    {
        g[0] = 0;
        memset(hash, 0, sizeof(hash));
        memset(no, 0, sizeof(no));

        for(i = 1; i <= n; i++)
        {
            scanf("%d", &g[i]);
            g[i] += g[i-1];
        }
        for(i = 0; i < m; i++)
        {
            scanf("%d", &rt);
            hash[rt] ++;
        }

        u = 0;
        sum = 0;

        for(i = 1; i <= n; i++)
        {
            if(hash[i])
            {
                no[i] = no[u] + g[i] - g[u];

                sum += hash[i] < no[i] ? hash[i] : no[i];

                no[i] -= (hash[i] < no[i] ? hash[i] : no[i]);
                u = i;
                //printf("%d\n", u);
            }
        }

        printf("%d\n", sum);
    }
}
