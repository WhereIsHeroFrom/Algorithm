#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
struct point
{
    int x;
    int y;
};

/**** **** **** **** **** ****
 *    Function Name :          高斯消元法
*     Description :            求解线性方程组
*     void exchange_col(int p1,int p2,int n)  
*     交换p1行和p2行的所有数据
*     bool gauss(int n)
*     求解系数矩阵为n的线性方程组，方程组无解返回false，否则true
**** **** **** **** **** ****/ 
const int num = 400;
double matrix[num][num + 1];  //系数矩阵，从0开始
double ans[num];           //结果数组
void exchange_col(int p1,int p2,int n) //交换p1行和p2行的所有数据
{
     double t;
     int i;
     for(i = 0 ; i <= n ; i++)
     {
            t = matrix[p1][i];
            matrix[p1][i] = matrix[p2][i];
            matrix[p2][i] = t;
     }
}
bool gauss(int n) //求解系数矩阵为n的线性方程组
{
     int i,j,k;
     int p;
     double r;
     
     for(i = 0 ; i < n - 1; i++) 
     {
          p = i;
          for(j = i + 1 ; j < n ; j++)
          {   
               //寻找i列最大值位置
               if(matrix[j][i] > matrix[p][i])
                    p = j;
          }

          if(p != i)     exchange_col(i, p, n);         
          
          if(fabs(matrix[i][i]) < 1e-17)
          {
              continue;
          }
          for(j = i + 1 ; j < n ; j++) 
          {       //剩余列进行消元
             
               r = matrix[j][i] / matrix[i][i];
               for(k = i ; k <= n ; k++)
                    matrix[j][k] -= r * matrix[i][k];
          }
     }
     for(i = n - 1 ; i >= 0 ; i--) 
     {   //获得结果
          ans[i] = matrix[i][n];
          for(j = n - 1 ; j > i ; j--)
               ans[i] -= matrix[i][j] * ans[j];   
          if(fabs(matrix[i][i]) < 1e-17)
              continue;
          ans[i] /= matrix[i][i];
     }
     return true;
}

char map[400][400];
int dir[4][2]= {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;
int top;
int stack[100], Top;
int hash[100][100];
int Num(int x, int y)
{
    return x*m + y;
}
queue < point > q; 

int Bfs(int x, int y)
{
    while(!q.empty())
        q.pop();
    
    point temp;
    point tt;
    temp.x = x;
    temp.y = y;
    q.push(temp);
    
    while(!q.empty())
    {
        int i;
        temp = q.front();
        q.pop();
        if(map[temp.x][temp.y] == '$')
            return 1;
        for(i = 0; i < 4; i++)
        {
            tt.x = temp.x + dir[i][0];
            tt.y = temp.y + dir[i][1];
            if(tt.x < 0 || tt.y < 0 || tt.x >= n || tt.y >= m)
                continue;
            if(!hash[tt.x][tt.y] && map[tt.x][tt.y] != '#')
            {
                hash[tt.x][tt.y] = 1;
                q.push(tt);
            }
        }
    }
    return 0;
    
}
int main()
{
    int i, j, k;
    int tx, ty, p;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(i = 0; i < n; i++)
            scanf("%s", map[i]);
        
        p = -1;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                if(map[i][j] == '@')
                {
                    p = Num(i, j);
                    tx = i;
                    ty = j;
                    break;
                }
            }
        }
        memset(hash, 0, sizeof(hash));
        hash[tx][ty] = 1;
        
        if( !Bfs(tx, ty))
        {
            printf("-1\n");
            continue;
        }
        
        for(i = 0; i <= 300; i++)
            for(j = 0; j <= 300; j++)
                matrix[i][j] = 0;
        
        for(i = 0; i <= 300; i++)
           matrix[i][n*m] = 1;
        
        top = 0;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m ; j++)
            {
                int coun = 0;
                Top = 0;
                if(map[i][j] == '$' || map[i][j] == '#')
                {
                    matrix[top][Num(i, j)] = 1.0;
                    matrix[top][n*m] = 0;
                    top++;
                    continue;
                }
                for(k = 0; k < 4; k++)
                {
                     tx = i + dir[k][0];
                     ty = j + dir[k][1];
                     if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                     {
                         continue;
                     }
                     if(map[tx][ty] != '#')
                     {
                         stack[Top++] = Num(tx, ty);
                         coun++;                         
                     }
                }
                if(coun == 0)
                {
                    matrix[top][n*m] = 0;
                    matrix[top][Num(i, j)] = 1;
                }else
                {
                    matrix[top][Num(i, j)] = coun;
                    matrix[top][n*m] = coun;
                
                    for(k = 0; k < Top; k++)
                    {
                        matrix[top][stack[k]] = -1.0;
                    }
                }
                top++;
            }
        }
        
        /*for(i = 0; i < n*m; i++)
        {
            for(j = 0; j <= n*m; j++)
                printf("%.3lf ", matrix[i][j]);
            puts("");
        }*/
        
        gauss(n*m);
        printf("%.6lf\n", ans[p]);
    }
}

/*
 10 10
@#########
..........
....#.....
...#$#....
....#.....
..........
.#.....#..
..........
..........
........#$

3 3
@..
..#
.#$
 */

