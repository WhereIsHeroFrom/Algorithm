#include <iostream>
using namespace std;
int dir[4][2] ={{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
struct point
{
    int x;
    int y;
    int num;
    int value;
}buf, Min;
int n, m, hash[30][30];

int top;
char map[30][30];
char ori[30][30];
point stack[ 1000 ];
int zong;

point Mine[ 1000 ];
int zty;

int dfs(char c, int x, int y)
{
    int i;
    int tx, ty;
    int sum = 1;
    for(i = 0; i < 4; i++)
    {
        tx = x + dir[i][0];
        ty = y + dir[i][1];
        if(tx < 0 || ty < 0 || tx >= n || ty >= m)
            continue;
        if(!hash[tx][ty] && c == map[tx][ty])
        {
            hash[tx][ty] = 1;
            sum += dfs(c, tx, ty);
        }
    }
    return sum;
}

char rt[30][30];
int has[30][30];

int DFS(char c, int x, int y)
{
    int i;
    int tx, ty;
    int sum = 1;
    for(i = 0; i < 4; i++)
    {
        tx = x + dir[i][0];
        ty = y + dir[i][1];
        if(tx < 0 || ty < 0 || tx >= n || ty >= m)
            continue;
        if(!has[tx][ty] && c == rt[tx][ty])
        {
            has[tx][ty] = 1;
            sum += DFS(c, tx, ty);
        }
    }
    return sum;
}

int Rt_One() {

    int sum = 0;
    int coun = 0;
    int i, j, k;
    zong = 0;

    while(1)
    {       
        coun++;
        top = 0;
        int flag = 0;
        memset(hash, 0, sizeof(hash));
        Min.num = -1;
        for(i = 0; i < n ;i++)
        {
            for(j = 0; j < m; j++)
            {
                if(!hash[i][j] && (map[i][j]-'0'))
                {
                    hash[i][j] = 1;
                    buf.num = dfs(map[i][j], i, j);
                    if(buf.num == 1)
                        continue;
                    buf.x = i;
                    buf.y = j;
                    
                    if(buf.num > Min.num)
                    {
                        Min = buf;     
                        flag = 1;
                    }else if(buf.num == Min.num)
                    {
                        if(buf.x < Min.x)
                        {
                            Min = buf;
                            flag = 1;
                        }else if(buf.x == Min.x && buf.y < Min.y)
                        {
                            Min = buf;
                            flag = 1;
                        }
                    }
                }
            }
        }
        if(!flag)
            break;
        stack[ zong++ ] = Min;
        sum += Min.num * (Min.num - 1);

        memset(hash, 0, sizeof(hash));
        hash[Min.x][Min.y] = 1;
        dfs(map[Min.x][Min.y], Min.x, Min.y);
        
        for(i = 0; i <  n ;i++)
        {
            for(j = 0; j < m; j++)
            {
                if(hash[i][j])
                    map[i][j] = '0';
            }
        }
        
        for(i = 1; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                if(! (map[i][j] - '0') )
                {
                    for(k = i; k > 0; k--)
                    {
                        map[k][j] = map[k-1][j];
                    }
                    map[0][j] = '0';
                }
            }
        }
   
        for(i = m-1; i >= 0; i--)
        {
            if(map[n-1][i] == '0')
            {
                for(j = 0; j < n; j++)
                {
                    for(k = i ; k < m; k++)
                    {
                        map[j][k] = map[j][k+1];
                    }
                }
            }
        }
    }
    return sum;
}

int process(int x, int y, int ID) {

    int i, j, k;
    point Min;
    Min.x = x;
    Min.y = y;

    memset(rt, '\0', sizeof(rt));

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            rt[i][j] = map[i][j];
            has[i][j] = hash[i][j];
        }
    }
    
    has[Min.x][Min.y] = 1;
    memset(has, 0, sizeof(has));
    DFS(rt[Min.x][Min.y], Min.x, Min.y);
    
    for(i = 0; i < n; i++) {
        for(j = 0;j < m; j++) {
            if(has[i][j])
                rt[i][j] = '0';
        }
    }
    
    for(i = 1; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(! (rt[i][j] - '0') )
            {
                for(k = i; k > 0; k--)
                {
                    rt[k][j] = rt[k-1][j];
                }
                rt[0][j] = '0';
            }
        }
    }

    for(i = m-1; i >= 0; i--)
    {
        if(rt[n-1][i] == '0')
        {
            for(j = 0; j < n; j++)
            {
                for(k = i ; k < m; k++)
                {
                    rt[j][k] = rt[j][k+1];
                }
            }
        }
    }

    int coun = 0;
    memset(has, 0, sizeof(has));
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(!has[i][j] && rt[i][j] != '0') {
                has[i][j] = 1;
                int ty = DFS(rt[i][j], i, j);
                coun += ty * (ty - 1);
            }
        }
    }
    return coun;
}

int Rt_Two() {

    int sum = 0;
    int coun = 0;
    int i, j, k;
    zong = 0;

    while(1)
    {       
        coun++;
        top = 0;
        int flag = 0;
        memset(hash, 0, sizeof(hash));
        Min.value = 0;
        for(i = 0; i < n ;i++)
        {
            for(j = 0; j < m; j++)
            {
                if(!hash[i][j] && (map[i][j]-'0'))
                {
                    hash[i][j] = 1;
                    buf.num = dfs(map[i][j], i, j);

                    if(buf.num == 1)
                        continue;

                    buf.value = process(i, j, coun) + buf.num * (buf.num - 1);
                    buf.x = i;
                    buf.y = j;
                    
                    if(buf.value > Min.value)
                    {
                        Min = buf;
                        flag = 1;
                    }
                }
            }
        }
        if(!flag)
            break;

        stack[ zong++ ] = Min;
        sum += Min.num * (Min.num - 1);

        memset(hash, 0, sizeof(hash));
        hash[Min.x][Min.y] = 1;

        dfs(map[Min.x][Min.y], Min.x, Min.y);
        
        for(i = 0; i <  n ;i++)
        {
            for(j = 0; j < m; j++)
            {
                if(hash[i][j])
                    map[i][j] = '0';
            }
        }
        
        for(i = 1; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                if(! (map[i][j] - '0') )
                {
                    for(k = i; k > 0; k--)
                    {
                        map[k][j] = map[k-1][j];
                    }
                    map[0][j] = '0';
                }
            }
        }
   
        for(i = m-1; i >= 0; i--)
        {
            if(map[n-1][i] == '0')
            {
                for(j = 0; j < n; j++)
                {
                    for(k = i ; k < m; k++)
                    {
                        map[j][k] = map[j][k+1];
                    }
                }
            }
        }
    }
    return sum;
}

int main()
{
    int i, j, k;
    int Max_op = 0;
    int op
        ;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(i = 0; i < n; i++)
            scanf("%s", ori[i]);
        for(i = 0; i <= m; i++)
            ori[n][i] = '0';
        for(i = 0; i <= n; i++)
            ori[i][m] = '0';

        Max_op = 0;
        for(i = 0; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                map[i][j] = ori[i][j];
            }
        }
        op = Rt_One();
        if(op > Max_op) {
            Max_op = op;
            zty = 0;
            for(i = 0; i < zong; i++)
                Mine[ zty++ ] = stack[i];
        }

        for(i = 0; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                map[i][j] = ori[i][j];
            }
        }
        op = Rt_Two();
        if(op > Max_op) {
            Max_op = op;
            zty = 0;
            for(i = 0; i < zong; i++)
                Mine[ zty++ ] = stack[i];
        }
        printf("%d\n", zty);
        for(i = 0; i < zty; i++) {
            printf("%d %d\n", Mine[i].x, Mine[i].y);
        }
    }

}

