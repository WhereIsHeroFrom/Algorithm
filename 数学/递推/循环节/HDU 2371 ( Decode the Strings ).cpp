#include <iostream>
using namespace std;
struct XunHuan
{
    int a[220];         //该循环段中有的元素下标
    int num;            //该循环段下标的个数
    int Xu;              //该循环段的循环节
}Qun[220];

int zong;               //置换群的循环节个数
int n;                  
int ZhiHuan[220];
char map[220];
int hash[220];

int Test(int index, XunHuan temp)
{
    int i;
    int buf[220];
    int coun = 0;
    memset(buf, 0, sizeof(buf));
    while(1)
    {
        for(i = 0; i < temp.num; i++)
        {
            buf[i] = ZhiHuan[temp.a[i]];
        } 
        coun ++;
        for(i = 0; i < temp.num; i++)
            if(Qun[index].a[i] != buf[i])
                break;
        if(i == temp.num)
            return coun;
        for(i = 0; i < temp.num; i++)
        {
            temp.a[i] = buf[i];
        } 
    }
}

int main()
{
    int k;
    int i, j, l;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        if(!n && !k)
            break;
         for(i = 1; i <= n; i++)
             scanf("%d", &ZhiHuan[i]);         
         zong = 0;

         for(i = 1; i <= n; i++)
         {
             if(!hash[i])
             {
                 hash[i] = 1;
                 Qun[zong].num = 0;
                 Qun[zong].a[ Qun[zong].num++] = i;
                 int u = i;
                 while(1)
                 {
                     if(!hash[ ZhiHuan[u] ])
                     {
         
               hash[ ZhiHuan[u] ] = 1;
                         Qun[zong].a[ Qun[zong].num++] = ZhiHuan[u];
                         u = ZhiHuan[u];
                     }else
                         break;
                 }
                 zong ++;
             }
         }
         for(i = 0; i < zong; i++)
         {
             Qun[i].Xu = Test(i, Qun[i]);        //检测单个循环段的循环节
         }

         //while( scanf("%d", &k) != EOF && k)
         {
              memset(hash, 0, sizeof(hash));
              getchar();
              gets(&map[1]);
              int len = strlen(&map[1]);
              for(i = len + 1; i <= n; i++)
              {
                  map[i] = ' ';

              }

              char budg[220];
              memset(budg, '\0', sizeof(budg));
              int buf[220];
              

              for(i = 0; i < zong; i++)
              {
                  XunHuan temp;
                  temp.num = Qun[i].num;

                  for(j = 0; j < temp.num; j++)
                      temp.a[j] = Qun[i].a[j];

                  int Num = k % Qun[i].Xu;
                  for(j = 0; j < Num ; j++)
                  {
                        for(l = 0; l < temp.num; l++)
                        {
                            buf[l] = ZhiHuan[temp.a[l]];
                        }
                        for(l = 0; l < temp.num; l++)
                        {
                            temp.a[l] = buf[l];
                        }
                  }
                  for(j = 0; j < temp.num; j++)
                  {
                      budg[temp.a[j]] = map[ Qun[i].a[j] ];
                  } 

              }
              puts(&budg[1]);
         }
    }
    return 0;
}
