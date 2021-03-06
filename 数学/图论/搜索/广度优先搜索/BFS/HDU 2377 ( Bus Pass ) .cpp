#include <iostream>
#include <queue>
using namespace std;

struct point
{
    int x;
    int step;
};

int map[10000][11];
int num[10000];
int hash[10000];
int visit[201][10000];
int stack[201], top;
int h, m, t;
int k, ty, rt, u, v;

int Bfs(int start, int n)
{
    int i;
    queue < point > q;
    point temp, tt;
    temp.step = 1;
    temp.x = start;
    visit[n][start] = 1;
    q.push(temp);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        for(i = 0; i < num[temp.x]; i++)
        {
            tt.x = map[temp.x][i];
            tt.step = temp.step + 1;
            if(visit[n][tt.x] == -1 || tt.step < visit[n][tt.x])
            {
                visit[n][tt.x] = tt.step;
                q.push(tt);
            }
        }
    }
    return 0;
}
int main()
{
    int i, j;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &m, &h);
        memset(map, 0, sizeof(map));
        memset(num, 0, sizeof(num));
        memset(hash, 0, sizeof(hash));
        memset(visit, -1, sizeof(visit));
        for(i = 0; i < m; i++)
        {
            scanf("%d %d", &k, &ty);
            num[k] = ty;
            for(j = 0; j < ty; j++)
            {
                scanf("%d", &rt);
                map[k][j] = rt;
            }
        }
        top = 0;
        for(i = 0; i < h; i++)
        {
            scanf("%d", &u);
            for(j = 0; j < u; j++)
            {
                scanf("%d", &v);
                if(!hash[v])
                {
                    stack[top++] = v;
                }
            }
        }
        for(i = 0; i < top; i++)
        {
            Bfs(stack[i], i);
        }
        bool flag;
        int Min = INT_MAX, u, Max;
        for(j = 0; j <= 9999; j++)
        {    
            Max = INT_MIN;
            flag = false;
            for(i = 0; i < top; i++)
            {
                if(visit[i][j] != -1 && visit[i][j] > Max)
                {
                    flag = true;
                    Max = visit[i][j];
                }
            }
            if(flag && Max < Min)
            {
                Min = Max;
                u = j;
            }
        }printf("%d %d\n",  Min, u);
    }
}
