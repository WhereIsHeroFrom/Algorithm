#include <iostream>
#include <cmath>
using namespace std;
int len[101];
int State(int from, int to, int coun)
{
  int i;
  if(from == to)
    return 0;
  int pre[33], top1 = 0;
  int next[33], top2 = 0;
  i = 0;
  while(i < coun)
  {
    pre[top1++] = from & 1;
    from >>= 1;

    next[top2++] = to & 1;
    to >>= 1;
    
    i++;
  }
  int cou = 0;
  for(i = 0; i < top1; i++)
  {
    if(pre[i] && !next[i])
      return 0;
    if(!pre[i] && next[i])
        cou++;
  }
  return 1;
}

char ch[1000];
double dot[1000];
double f[110][1<<7];
int vec[8][1<<7][1<<7];
int Num[8][1<<7];
int main()
{
  int i, j, coun;
  int t, n, k;
  int num;
  for(i = 1; i <= 900; i++)
      dot[i] = 1.0/i;
  for(num = 1; num <= 7; num++)
  {
      int q = (1<<num);
      for(i = 0; i < q; i++)
      {
          int u = (1<<num);
          for(j = i+1; j < u; j++)
          {
               if(State(i, j, num))
                    vec[num][i][Num[num][i]++] = j;
          }
      }
  }
  scanf("%d", &t);
  while(t--)
  {
    scanf("%d", &n);
    int Max = -1;
    for(i = 0; i < n; i++)
    {
      scanf("%s", ch);
      len[i] = strlen(ch);
      if(len[i] > Max)
          Max = len[i];
    }
    
    for(i = 0; i <= 10; i++)
    {
        int fg = (1<<n);
        for(j = 0; j < fg; j++)
        {
           f[i][j] = 0;
        }
    }
    int tyty = 0;
    f[0][0] = 1.0;
    double sum = 0;
    if(Max > 10)
        Max = 10;
    for(i = 1; i <= Max; i++)
    {
      for(j = (1<<n)-1; j >= 0; j--)
      {        
          if(i == 1 && j)
              continue;
        //printf("%d\n", Num[n][j]);
        for(k = 0; k < Num[n][j]; k++)
        {
              int v = vec[n][j][k];

              int ty = (j^v);
              double p = 1;
              coun = 0;
              while(coun < n)
              {
                int u = ty & 1;
                if(!u)
                {
                    if(      ( (1<<coun) & j)    )
                    {
                        coun++;
                        ty >>= 1;
                        continue;
                    }
                    if(len[coun] < i)
                        p *= 1;
                    else if(len[coun] >= i)
                    {
                        p *= (1 - dot[(len[coun]+1-i)]);
                        if(p == 0)
                            break;
                    }
                }else
                {
                    if(len[coun] < i)
                        break;
                    else if(len[coun] >= i)
                    {
                        p *= dot[(len[coun]+1-i)];
                    }                    
                }
                coun++;
                ty >>= 1;
              }
                  
              f[i][v] += f[i-1][j]*p;
        }
      }
      if(fabs(f[i][(1<<n)-1]) < 1e-7)
          break;
      sum += f[i][(1<<n)-1];
    }
    
    /*for(i = 0; i <= 5; i++)
    {
        for(j = 0; j < (1<<n); j++)
            printf("%lf ", f[i][j]);
        puts("");
    }*/
    
    printf("%.3lf\n", sum);
  }

}

