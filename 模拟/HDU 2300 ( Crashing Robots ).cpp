#include <iostream>
using namespace std;
struct robot
{
    int x;
    int y;
    int dir;
}p[10001];
int dir[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
char ch[4] = {'E', 'S', 'W', 'N'};
int hash[101][101];
int t, n, m;
int num, cas;
int i, j;
int flag = 0;
int a, b, start, end;
char c[100];
char buf[100];
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        memset(hash, 0, sizeof(hash));
        scanf("%d%d", &m, &n);
        scanf("%d%d", &num, &cas);
        for(i = 1; i <= num; i++)
        {
            scanf("%d%d%s", &p[i].y, &p[i].x, c);
            for(j = 0; j < 4; j++)
                if(c[0] == ch[j])
                    p[i].dir = j;
            hash[p[i].y][p[i].x] = i;
        }
        flag = 0;
        start = -1;
        end = -1;
        while(cas--)
        {
            scanf("%d%s%d", &a, buf, &b);
            if(!flag)
            {
                for(i = 0; i < b; i++)
                {
                    if(buf[0] == 'L')
                    {
                        p[a].dir = (p[a].dir + 3) % 4;
                    }
                    else if(buf[0] == 'R')
                    {
                        p[a].dir = (p[a].dir + 1) % 4;
                    }
                    else
                    {
                        hash[p[a].y][p[a].x] = 0;

                        p[a].x += dir[p[a].dir][0];
                        p[a].y += dir[p[a].dir][1];
                        if(p[a].x == 0 || p[a].y == 0
                            || p[a].x == n+1 || p[a].y == m+1)
                        {
                            //printf("(%d %d %d)", a, p[a].x, p[a].y);
                            flag = 1;
                            start = a;
                            break;
                        }
                        if(hash[p[a].y][p[a].x])
                        {
                            flag = 1;
                            start = a;
                            end = hash[p[a].y][p[a].x];
                            break;
                        }
                        
                        hash[p[a].y][p[a].x] = a;

                    }
                }
            }
        }
        if(!flag)
        {
            printf("OK\n");
        }else
        {
            if(end == -1)
                printf("Robot %d crashes into the wall\n", start);
            else
                printf("Robot %d crashes into robot %d\n", start, end);
        }
    }
}
