#include <iostream>
#include <queue>
using namespace std;

int dir[4][2] = 
{
    {-1, 0}, 
    {1, 0}, 
    {0, -1}, 
    {0, 1}
};

struct point
{
    int sec;
    int step;
    int x;
    int y;
    bool friend operator < (point a, point b){
        return a.step > b.step;
    }

}temp, tt;

char map[32][32];
int n, m;
int i, j, k;
int hash[32][32][5];

priority_queue < point > q;

int main()
{
    int t, i, j;
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d %d", &n, &m);

        for(i = 0; i < n; i++)
            scanf("%s", map[i]);

        for(i = 0; i < n; i++){
            for(j = 0; j < m; j++){
                if(map[i][j] == '&'){
                    temp.sec = 0;
                    temp.step = 0;
                    temp.x = i;
                    temp.y = j;

                    map[i][j] = '-';
                }
            }
        }

        while(!q.empty())
            q.pop();

        memset(hash, 0, sizeof(hash));
        q.push( temp );

        int flag = -1;

        while(!q.empty()){

            temp = q.top();
            q.pop();

            if(map[temp.x][temp.y] == '~'){
                flag = temp.step;
                break;
            }

            for(i = 0; i < 4; i++){

                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];

                if(tt.x < 0 || tt.x >= n)
                    continue;

                if(tt.y < 0)
                    tt.y += m;
                tt.y %= m;

                if(hash[tt.x][tt.y][temp.sec % 5])
                    continue;

                if(map[tt.x][tt.y] == 'T')
                    continue;

                //直接走, 能走通并且不被撞就走

                tt.sec = temp.sec + 1;

                for(k = 0; k < m; k++)
                {
                    if(map[tt.x][k] == '>')
                    {
                        if( (k + tt.sec) % m == tt.y )
                            break;
                    }

                    if(map[tt.x][k] == '<')
                    {
                        if( (k - tt.sec + 1000 * m) % m == tt.y )
                            break;
                    }
                }

                if(k == m)
                {        
                    hash[ tt.x ][ tt.y ][ temp.sec % 5] = 1;
                    if(map[temp.x][temp.y] == '-'
                        || map[temp.x][temp.y] == '<'
                        || map[temp.x][temp.y] == '>')
                        tt.step = temp.step + 1;
                    else
                        tt.step = temp.step;
                    q.push( tt );
                }

                //停j秒，然后在j+1秒能走就走，（如果前j秒将要被撞直接跳出）

                for(j = 1; j <= m; j++)
                {
                    tt.sec = temp.sec + j;
                    for(k = 0; k < m; k++)
                    {
                        if(map[temp.x][k] == '>')
                        {
                            if( (k + tt.sec) % m == temp.y )
                                break;
                        }

                        if(map[temp.x][k] == '<')
                        {
                            if( (k - tt.sec + 1000 * m) % m == temp.y )
                                break;
                        }
                    }

                    if(k == m)
                    {
                        tt.sec = temp.sec + j + 1;
                        for(k = 0; k < m; k++)
                        {
                            if(map[tt.x][k] == '>')
                            {
                                if( (k + tt.sec) % m == tt.y )
                                    break;
                            }

                            if(map[tt.x][k] == '<')
                            {
                                if( (k - tt.sec + 1000 * m) % m == tt.y )
                                    break;
                            }
                        }

                        if(k == m)
                        {    
                            hash[ tt.x ][ tt.y ][ temp.sec % 5] = 1;
                            if(map[temp.x][temp.y] == '-'
                                || map[temp.x][temp.y] == '<'
                                || map[temp.x][temp.y] == '>')
                                tt.step = temp.step + j + 1;
                            else
                                tt.step = temp.step;
                            q.push( tt );
                        }
                    }else
                        break;
                }
    
            }
        }
        if(flag == -1)
            printf("Impassable\n");
        else
            printf("%d\n", flag);
    }

    return 0;
}
