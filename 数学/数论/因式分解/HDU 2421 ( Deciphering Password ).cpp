#include <iostream>
#include <cmath>
using namespace std;

int f[65537];
int p[65537], size;
int pri[1000], num[1000], zong;

void init()
{
  int i, j;
  f[0] = 1;
  f[1] = 1;
  size = 0;
  for(i = 2; i <= 65536; i++)
  {
    if(!f[i])
    {
      p[size++] = i;
      for(j = i+i; j <= 65536; j += i)
      {
        f[j] = 1;
      }
    }
  }
}

void FactorSum(int u)
{
      int sqr = (int)sqrt(u * 1.0);

      int i, d = u;

      zong = 0;

      for(i = 0; i < size && p[i] <= sqr; i++)
      {
            if(u % p[i] == 0)
            {
                  pri[zong] = p[i];
                  num[zong] = 1;
                  u /= p[i];
                  while(u % p[i] == 0)
                  {
                    num[zong] ++;
                    u /= p[i];
                  }
                  zong++;
            }
            if(u <= 65536 && !f[u])
            {
                  num[zong] = 1;
                  pri[zong] = u;
                  u = 1;
                  zong++;
                  break;
            }
            if(u == 1)
                break;
      }
      if(u != 1)
      {
          num[zong] = 1;
          pri[zong] = u;
          u = 1;
          zong++;
      }
} 

__int64 b;

__int64 pro(__int64 ty)
{
    ty *= b;
    __int64 er;
    if(ty % 2 == 0)
    {
        er = (ty + 2) / 2 * (ty + 1) % 10007;
        er *= er;
        er %= 10007;
        return er;
    }else
    {
        er = (ty + 1) / 2 * (ty + 2) % 10007;
        er *= er;
        er %= 10007;
        return er;
    }

}

int main()
{
    int a, c = 1;
    int i;
    __int64 ans;
    init();
    while(scanf("%d %I64d", &a, &b) != EOF)
    {
        printf("Case %d: ", c++);
        if(a == 1)
        {
            printf("1\n");
            continue;
        }
        FactorSum(a);
        /*for(i = 0; i < zong; i++)
        {
            printf("%d %d\n", pri[i], num[i]);
        }*/

        ans = 1;

        for(i = 0; i < zong; i++)
        {
            ans = ans * (pro(num[i])) % 10007;
        }

        printf("%I64d\n", ans);



    }
}
