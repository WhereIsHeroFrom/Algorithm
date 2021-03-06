#include <iostream>

using namespace std;

struct point
{
    int x;
    int y;
    int dir;
}temp, tt;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char ch[4] = {'^', '>', 'v', '<'};
char map[22][22];
char str[1000];


void process()
{
    int i;
    if(temp.dir == 0)
    {
        if(tt.x < 1)
            tt.x = 1;
        for(i = tt.x; i < temp.x; i++)
            map[i][temp.y] = map[i+1][temp.y];
    }else if(temp.dir == 1)
    {
        if(tt.y > 8)
            tt.y = 8;
        for(i = tt.y; i > temp.y; i--)
            map[temp.x][i] = map[temp.x][i-1];
    }else if(temp.dir == 2)
    {
        if(tt.x > 8)
            tt.x = 8;
        for(i = tt.x; i > temp.x; i--)
            map[i][temp.y] = map[i-1][temp.y];
    }else
    {
        if(tt.y < 1)
            tt.y = 1;
        for(i = tt.y; i < temp.y; i++)
            map[temp.x][i] = map[temp.x][i+1];
    }
    temp.x += dir[temp.dir][0];
    temp.y += dir[temp.dir][1];
}
int main()
{
    int i, j, k, n;
    while(scanf("%s", &map[1][1]) != EOF)
    {
        if(strcmp(&map[1][1], "--") == 0)
            break;
        for(i = 2; i <= 8; i++)
            scanf("%s", &map[i][1]);

        for(i = 1; i <= 8; i++)
        {
            for(j = 1; j <= 8; j++)
            {
                for(k = 0; k < 4; k++)
                {
                    if(map[i][j] == ch[k])
                        break;
                }
                if(k < 4)
                {
                    temp.x = i;
                    temp.y = j;
                    temp.dir = k;
                    map[i][j] = '.';
                }
            }
        }

        while(scanf("%s", str) != EOF)
        {
            if(strcmp(str, "#") == 0)
                break;
            if(strcmp(str, "move") == 0)
            {
                scanf("%d", &n);
                for(i = 0; i < n; i++)
                {
                    tt.x = temp.x + dir[temp.dir][0];
                    tt.y = temp.y + dir[temp.dir][1];
                    if(tt.x < 1 || tt.y < 1 || tt.x > 8 || tt.y > 8)
                        break;
                    while(map[tt.x][tt.y] != '.')
                    {                    
                        tt.x += dir[temp.dir][0];
                        tt.y += dir[temp.dir][1];
                        if(tt.x < 1 || tt.y < 1 || tt.x > 8 || tt.y > 8)
                            break;
                    }
                    process();
                }
            }else
            {
                scanf("%s", str);
                if(strcmp(str, "right") == 0)
                {
                    temp.dir = ( temp.dir + 1 ) % 4;
                }else if(strcmp(str, "left") == 0)
                {
                    temp.dir = ( temp.dir + 3 ) % 4;
                }else
                {
                    temp.dir = ( temp.dir + 2 ) % 4;
                }
            }
        }

        for(i = 1; i <= 8; i++)
        {
            for(j = 1; j <= 8; j++)
            {
                if(temp.x == i && temp.y == j)
                    printf("%c", ch[ temp.dir ]);
                else
                    printf("%c", map[i][j]);
            }
            puts("");
        }
        puts("");
    }

}
