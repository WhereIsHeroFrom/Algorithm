#include <iostream>
#include <algorithm>
using namespace std;
int map[21][4];
int stack[22];
int top = 0;
int start;
int hash[22];
int coun;
void dfs(int m, int depth)
{
    int i;
    if(depth == 20)
    {
        printf("%d: ", coun ++);
        for(i=0;i<top;i++)
        {
            printf(" %d", stack[i]);
        }
        printf("\n");
        
    }else
    {
        if(m == start && depth != 0)
            return ;
    }
    for(i=0;i<3;i++)
    {
        if(hash[ map[m][i] ] == 0)
        {
           hash[ map[m][i] ] = 1;
           stack[top++] = map[m][i];
           dfs(map[m][i], depth + 1);
           hash[ map[m][i] ] = 0;
           top --;
        }
    }
}
int i, m;
int main()
{
    while(scanf("%d%d%d", &map[1][0], &map[1][1], &map[1][2])!=EOF)
    {
          sort(map[1], map[1] + 3);
          for(i=2;i<=20;i++)
          {
               scanf("%d%d%d", &map[i][0], &map[i][1], &map[i][2]);
               sort(map[i], map[i] + 3);
               //printf("%d%d%d", map[i][0], map[i][1], map[i][2]);
          }
          while(1)
          {
               scanf("%d", &m);
               if(!m)break;
               top = 0;
               memset(hash, 0, sizeof(hash));
               start = m;
               stack[top++] = m;
               coun = 1;
               dfs(m, 0);
          }
    }
}
