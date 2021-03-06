#include <iostream>
#include <queue>
using namespace std;

struct point
{
    int x;
    int y;
    int step;
    friend bool operator < (point a, point b)
    {
        return a.step > b.step;
    }
}temp, tt;

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int num[400];
int hash[50][50];
char map[50][50];
priority_queue < point > q;
int dx, dy;
int n, m;
int i, a, flag;

int main()
{
    int c = 1;
    while(scanf("%d %d", &n, &m) != EOF)
    {
        memset(hash, 0, sizeof(hash));

        for(i = 0; i < 3; i++)
        {
            scanf("%d", &a);
            if(i == 0) num['#'] = a;
            if(i == 1) num['.'] = a;
            if(i == 2) num['T'] = a;
        }
        
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        
        scanf("%d %d %d %d", &temp.x, &temp.y, &dx, &dy);
        temp.step = 0;
        hash[temp.x][temp.y] = 1;

        while(!q.empty())
            q.pop();

        q.push(temp);

        flag = -1;
        while(!q.empty())
        {
            temp = q.top();
            q.pop();
            //printf("%d %d\n", temp.x, temp.y);

            if(temp.x == dx && temp.y == dy)
            {
                flag = temp.step;
                break;
            }

            for(i = 0; i < 4; i++)
            {
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];

                if(tt.x >= n || tt.y >= m || tt.x < 0 || tt.y < 0)
                    continue;

                if(map[tt.x][tt.y] == '@')
                    continue;

                if(!hash[tt.x][tt.y])
                {
                    tt.step = temp.step + num[map[tt.x][tt.y]];
                    hash[tt.x][tt.y] = 1;
                    q.push(tt);
                }
            }
        }

        printf("Case %d: %d\n", c++, flag);
    }
}
