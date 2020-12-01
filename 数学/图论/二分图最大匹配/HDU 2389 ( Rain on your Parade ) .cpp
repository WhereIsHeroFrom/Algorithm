#include <iostream>
#include <cmath>
using namespace std;

#define MAX 3011
bool hash[MAX];
int map[MAX][MAX];
int coun[MAX];
int boy[MAX],gril[MAX];

struct point
{
    int x;
    int y;
}gue[MAX], um[MAX];

int speed[MAX];

int dis(int i, int j)
{
    int a = (gue[i].x-um[j].x);
    int b = (gue[i].y-um[j].y);
    return a*a + b*b;
}


bool dfs(int x)
{
    int temp, i;
    if(hash[x]) return false;
    hash[x] = true;
    for(i = 0;i < coun[x]; i++)
    {
        temp = map[x][i];
        if(gril[temp] == -1 || dfs(gril[temp]))
        {
           boy[x] = temp;
           gril[temp] = x;
           return true;
        }
    }
    return false;
}

int i, j;
int c = 1, t, n, m, tim;

int MaxMatch()
{
    int flag = 0, i;
    while(!flag)
    {
        flag = 1;
        memset(hash,0,sizeof(hash));

        for(i = 0; i < m; i++)
        {
             if(boy[i] == -1 && dfs(i))
                  flag = 0;
        }
    }
    int ans = 0;

    for(i = 0; i < m; i++)
    {
       if(boy[i] != -1)
           ans++;
    }

    return ans;
}


int main()
{
    scanf("%d",&t);

    while(t--)
    {
        memset(boy, -1, sizeof(boy));
        memset(gril, -1, sizeof(gril));

        scanf("%d", &tim);

        scanf("%d", &m);

        for(i = 0; i < m; i++)
        {
            scanf("%d %d %d", &gue[i].x, &gue[i].y, &speed[i]);
            coun[i] = 0;
        }

        scanf("%d",&n);

        for(i = 0; i < n; i++)
        {
            scanf("%d %d", &um[i].x, &um[i].y);
        }

        for(i = 0; i < m; i++)
        {
            for(j = 0; j < n; j++)
            {
                int ty = speed[i] * tim;
                if(dis(i, j) <= ty * ty)
                    map[i][ coun[i]++ ] = j;      //邻接表存边
            }
        }

        printf("Scenario #%d:\n%d\n\n", c++, MaxMatch());
    }
    return 0;
}
