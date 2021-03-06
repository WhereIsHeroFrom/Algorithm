#include <iostream>
#include <vector>
using namespace std;

int t;
int u, father[3001];
char str[3001];
int hash[2], T;
vector < int > vec[3001];

int dfs(int u)
{
    int sum = 0;
    int i, size = vec[u].size();
    if(size == 0)
        return 1;
    for(i = 0; i < size; i++)
    {
        int v = vec[u][i];
        sum += dfs(v);
    }
    return (sum * sum);
}
int main()
{
    int i, j;
    scanf("%d", &t);
    while(t--)
    {
        for(i = 0; i < 2; i++)
        {
            scanf("%s", str);
            T = 2;

            for(j = 0; j < 3001; j++)
                vec[j].clear();

            int len = strlen(str);
            u = 1;
            for(j = 0; j < len; j++)
            {
                if( str[j] == '0' )
                {
                    vec[u].push_back(T++);
                    father[T-1] = u;
                    u = T-1;
                }else
                {
                    u = father[u];
                }
            }
            hash[i] = dfs(1);
        }

        if(hash[0] == hash[1])
            printf("True\n");
        else
            printf("False\n");
    }
}

