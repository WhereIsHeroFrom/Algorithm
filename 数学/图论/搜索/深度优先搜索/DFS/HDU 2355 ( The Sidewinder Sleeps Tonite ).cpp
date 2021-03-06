#include <iostream>

using namespace std;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int h, w, t;
char map[100][100];
int hash[100][100];
int x, y;

void dfs(char c, int x, int y)
{
    int i, tx, ty;

    
    hash[x][y] = 1;
    if(c == '#')
    {
        for(i = 0; i < 4; i++)
        {
            tx = x + dir[i][0];
            ty = y + dir[i][1];
            if(tx <= 0 || ty <= 0 || tx > 2*h+1 || ty > 2*w+1)
                continue;
            if(!hash[tx][ty] && (map[tx][ty] == '|' || map[tx][ty] == '-'))
            {
                dfs(map[tx][ty], tx, ty);
                return;
            }
        }
    }else if(c == '-')
    {
        for(i = 0; i < 2; i++)
        {
            tx = x + dir[i][0];
            ty = y + dir[i][1];
            if(tx <= 0 || ty <= 0 || tx > 2*h+1 || ty > 2*w+1)
                continue;
            if(!hash[tx][ty] && map[tx][ty] == '#')
            {
                dfs(map[tx][ty], tx, ty);
                return;
            }
        }
    }else if(c == '|')
    {
        for(i = 2; i < 4; i++)
        {
            tx = x + dir[i][0];
            ty = y + dir[i][1];
            if(tx <= 0 || ty <= 0 || tx > 2*h+1 || ty > 2*w+1)
                continue;
            if(!hash[tx][ty] && map[tx][ty] == '#')
            {
                dfs(map[tx][ty], tx, ty);
                return;
            }
        }
    }
}

int main()
{
    int i, j, k;
    scanf("%d", &t);
    while(t--)
    {
        memset(hash, 0, sizeof(hash));
        scanf("%d%d", &h, &w);
        for(i = 1; i <= 2*h+1; i++)
            scanf("%s", &map[i][1]);

        x = -1;

        for(i = 1; i <= 2*h+1; i++)
        {
            for(j = 1; j <= 2*w+1; j++)
            {
                if(map[i][j] == '-' || map[i][j] == '|')
                {
                    x = i;
                    y = j;
                }
            }
        }
        int flag = 0;
        if(x == -1)
        {
            printf("INVALID\n");
            continue;


                for(i = 1; i <= 2*h+1; i++)
                {
                    for(j = 1; j <= 2*w+1; j++)
                    {
                        if(map[i][j] >= '0' && map[i][j] <= '9')
                        {
                            int coun = 0;
                            for(k = 0; k < 4; k++)
                            {
                                x = i + dir[k][0];
                                y = j + dir[k][1];
                                if(x <= 0 || y <= 0 || x > 2*h+1 || y > 2*w+1)
                                    continue;
                                if(hash[x][y] == 1)
                                    coun ++;
                            }
                            if(map[i][j] -'0'  != coun)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if(flag) break;
                    }
                    if(flag) break;
                }
                if(flag)
                    printf("INVALID\n");
                else
                    printf("VALID\n");
        }
        else
        {
            dfs(map[x][y], x, y);

            for(i = 1; i <= 2*h+1; i++)
            {
                for(j = 1; j <= 2*w+1; j++)
                {
                    if(hash[i][j] == 0 && (map[i][j] == '-' || map[i][j] == '|'))
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                    break;
            }
            if(flag)
                printf("INVALID\n");
            else
            {

                flag = 0;
                for(i = 1; i <= 2*h+1; i++)
                {
                    for(j = 1; j <= 2*w+1; j++)
                    {
                        if(map[i][j] == '#' && hash[i][j])
                        {
                            int coun = 0;
                            for(k = 0; k < 4; k++)
                            {
                                x = i + dir[k][0];
                                y = j + dir[k][1];
                                if(x <= 0 || y <= 0 || x > 2*h+1 || y > 2*w+1)
                                    continue;
                                if(hash[x][y] == 1)
                                    coun ++;
                            }
                            if(coun != 2)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if(flag) break;
                    }
                    if(flag) break;
                }

                if(flag)
                {
                    printf("INVALID\n");
                    continue;
                }




                for(i = 1; i <= 2*h+1; i++)
                {
                    for(j = 1; j <= 2*w+1; j++)
                    {
                        if(map[i][j] >= '0' && map[i][j] <= '9')
                        {
                            int coun = 0;
                            for(k = 0; k < 4; k++)
                            {
                                x = i + dir[k][0];
                                y = j + dir[k][1];
                                if(x <= 0 || y <= 0 || x > 2*h+1 || y > 2*w+1)
                                    continue;
                                if(hash[x][y] == 1)
                                    coun ++;
                            }
                            if(map[i][j] -'0'  != coun)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if(flag) break;
                    }
                    if(flag) break;
                }
                if(flag)
                    printf("INVALID\n");
                else
                    printf("VALID\n");
            }
        }
    }
}
/*
23
2 2
#-#-#
|?.?|
#.#-#
#.#.#
#.#.#
*/
