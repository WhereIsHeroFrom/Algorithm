#include <iostream>

using namespace std;

struct point
{
    int num;
    int degree;
};

int map[11][11];
int n;
int ColorNum()
{
    int i, j;
    int hash[11];                 //标记是否染色
    int num;                      //染色的点的数目
    int color[11];                //标记邻接已染色点
    int coun[11];                 //邻接染色点的数目
    int Max, u;                   //邻接染色点的数目最多的点
    int Maxd;                     //度数最大点
    point p[11];
    memset(hash, -1, sizeof(hash));
    
    for(i = 0; i < n; i++)
    {
        p[i].num = i;
        p[i].degree = 0;
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i != j && map[i][j])
                p[i].degree ++;
           
        }
    }
    
    u = -1;
    Max = -1;
    for(i = 0; i < n; i++)
    {
        if(p[i].degree > Max)
        {
            Max = p[i].degree;
            u = i;
        }
    }
    
    hash[u] = 0;
    num = 1;
    
    
    
    while(num < n)
    {
        memset(coun, 0, sizeof(coun));
        for(i = 0; i < n; i++)
        {
              memset(color, 0, sizeof(color));
              for(j = 0; j < n; j++)
              {
                  if(hash[j] != -1 && map[i][j] && i != j)
                  {
                      color [ hash[j] ] = 1;
                  }
              }
              for(j = 0; j < n; j++)
              {
                  if(color[j])
                      coun[i] ++;
              }
        }
        u = -1;
        Max = -1;
        
        for(i = 0; i < n; i++)
        {
            if(coun[i] > Max && hash[i] == -1)
            {
                Max = coun[i];
                u = i;
            }
        }
        
        for(i = 0; i < n; i++)
        {
            if(coun[i] == Max)
            {
                if(p[i].degree > Maxd && hash[i] == -1)
                {
                    Maxd = p[i].degree;
                    u = i;
                }
            }
        }
        
        memset(coun, 0, sizeof(coun));
        
        for(i = 0; i < n; i++)
        {
            if(i != u && map[i][u] && hash[i] != -1)
            {
                coun[ hash[i] ] = 1;
            }
        }
        
        for(i = 0; i < n; i++)
        {
            if(coun[i] == 0)
            {
                hash[u] = i;
                num ++;
                break;
            }
        }
    }
    
    int M = -1;
    for(i = 0; i < n; i++)
    {
        //printf("%d\n", hash[i]);
        if(hash[i] > M)
            M = hash[i];
    }
    return M + 1;
}
int main()
{
    int k, a, i, j, m;
    while(scanf("%d %d", &n, &m) != EOF)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                map[i][j] = 1;
            }
        }
        
        for(i = 0; i < n; i++)
        {
            scanf("%d", &k);
            
            for(j = 0; j < k;j++)
            {
                scanf("%d", &a);
                map[i][a] = map[a][i] = 0;
            }
        }
        
        if( ColorNum() <= m)
            printf("YES\n");
        else
            printf("NO\n");
    }
}

/*
5 4
4 1 2 3 4
3 0 2 3
2 0 1
2 0 1
1 0
 */
