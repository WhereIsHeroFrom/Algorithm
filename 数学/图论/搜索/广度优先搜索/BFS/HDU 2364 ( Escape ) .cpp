#include <iostream>

using namespace std;

int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct point
{
    int fro;
    int x;
    int y;
    int dir;
    int step;
}temp, tt;

int t, i, j;
point q[1000001];
int front, end;
char map[101][101];
bool hash[4][101][101];

int n, m;

int main()
{
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d %d", &n, &m);

        for(i = 0; i < n; i++)
        {
            scanf("%s", map[i]);
        }
        
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m ; j++)
            {
                if(map[i][j] == '@')
                {
                    temp.x = i;
                    temp.y = j;
                    temp.fro = -1;
                    temp.step = 0;

                    map[i][j] = '.';
                }
            }
        }

        memset(hash, 0, sizeof(hash));

        front = end = 0;
        for(i = 0; i < 4; i++)
        {
            temp.dir = i;
            hash[i][temp.x][temp.y] = 1;
            q[end++] = temp;
        }

        int step = -1;

        while(front < end)
        {
            temp = q[front++];
            tt.step = temp.step + 1;

            //printf("%d %d\n", temp.x, temp.y);

            if(temp.x == 0 || temp.y == 0 || temp.x == n - 1 || temp.y == m - 1)
            {
                step = temp.step;
                break;
            }
            int flag = 0;
            for(i = 0; i < 4; i++)
            {
                if(i == temp.dir)
                    continue;
                if(abs(i - temp.dir) == 2)
                    continue;
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];
                tt.dir = i;

                if(tt.x < 0 || tt.y < 0 || tt.x > n - 1 || tt.y > m - 1)
                    continue;
                if(map[tt.x][tt.y] == '#')
                    continue;

                flag = 1;
            }

            if(flag)
            {
                for(i = 0; i < 4; i++)
                {
                    if(i == temp.dir)
                        continue;
                    if(abs(i - temp.dir) == 2)
                        continue;
                    tt.x = temp.x + dir[i][0];
                    tt.y = temp.y + dir[i][1];
                    tt.dir = i;

                    if(tt.x < 0 || tt.y < 0 || tt.x > n - 1 || tt.y > m - 1)
                        continue;
                    if(map[tt.x][tt.y] == '#')
                        continue;
                    if(!hash[tt.dir][tt.x][tt.y])
                    {
                         hash[tt.dir][tt.x][tt.y] = 1;
                         q[end++] = tt;
                    }
                }
            }else
            {
                i = temp.dir;
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];
                tt.dir = i;

                if(tt.x < 0 || tt.y < 0 || tt.x > n - 1 || tt.y > m - 1)
                    continue;
                if(map[tt.x][tt.y] == '#')
                    continue;
                if(!hash[tt.dir][tt.x][tt.y])
                {
                    hash[tt.dir][tt.x][tt.y] = 1;
                    q[end++] = tt;
                }
            }
        }

        printf("%d\n", step);
    }
}

/*#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    int x;
    cin>>x;
    if(x==0)
       return 0;
    else
    {
        int *p=new int[x];
        for(int i=0;i<x;i++)
          cin>>p[i];
        int num=0;
        for(int j=0;j<x;j++)
            num+=p[j];
        num/=x;
        int result=0;
        for(int k=0;k<x;k++)
            result+=(abs(p[k]-num));
        result/=2;
        cout<<result<<endl;
    }
    while(cout<<endl)
    {
        cin>>x;
        if(x==0)
           return 0;
        else
        {
            int *p=new int[x];
            for(int i=0;i<x;i++)
                cin>>p[i];
            int num=0;
            for(int j=0;j<x;j++)
                num+=p[j];
            num/=x;
            int result=0;
            for(int k=0;k<x;k++)
                result+=(abs(p[k]-num));
            result/=2;
            cout<<result<<endl;
            
        }
    }
    return 0;
}*/
