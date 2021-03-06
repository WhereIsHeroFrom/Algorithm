#include <iostream>
#include <algorithm>
using namespace std;

int f[2536], p[2000], psize;
int sqr[1011], ssize; 
int cub[111], csize;
int qua[201], qsize;  
int t, stack[1001], top;
int x[1000], value[1000];
void init_pri()
{
    int i, j;
    f[0] = 1;
    f[1] = 1;
    psize = 0;
    for(i = 2; i < 2000; i++)
    {
        if(!f[i])
        {
            p[psize++] = i;
            for(j = i+i; j < 2000; j += i)
            {
                f[j] = 1;
            }
        }
    }

}

void init_sqr()
{
    int i;
    ssize = csize = qsize = 0;

    for(i = 1; i <= 1000; i++)
    {
        sqr[ssize++] = i*i;
    }

    for(i = 1; i <= 100; i++)
    {
        cub[csize++] = i*i*i;
    }

    for(i = 1; i <= 100; i++)
    {
        qua[qsize++] = i*i*i*i;
    }

}

int prime(int u)
{
    int i;
    if(u <= 1000)
        return !f[u];

    for(i = 0; i < psize; i++)
    {
        if(u % p[i] == 0)
            return 0;
    }
    return 1;
}

int sum_digi(int u)
{
    int t = u;
    int sum = 0;
    while(t)
    {
        sum += (t % 10);
        t /= 10;
    }
    return sum;
}

int nul_digi(int u)
{
    int t = u;
    int sum = 1;
    while(t)
    {
        sum *= (t % 10);
        if(sum > 1000000)
            return -1;
        t /= 10;
    }
    return sum;
}

int main()
{
    init_pri();
    init_sqr();
    int c = 1, n, i, j, k, l;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        memset(value, 0, sizeof(value));
        for(i = 0; i < n; i++)
        {
            scanf("%d", &x[i]);
        }

        for(i = 0; i < n; i++)
        {
            //prime test
            if(prime(x[i]))
                value[i] ++;

            for(j = 0; j < ssize; j++)
                if(x[i] == sqr[j])
                {
                    value[i]++;
                    break;
                }

            for(j = 0; j < csize; j++)
                if(x[i] == cub[j])
                {
                    value[i]++;
                    break;
                }

            for(j = 0; j < qsize; j++)
                if(x[i] == qua[j])
                {
                    value[i]++;
                    break;
                }

            if(sum_digi(x[i]) != -1 && x[i] % sum_digi(x[i]) == 0)
                value[i]++;

            int tp = nul_digi(x[i]);
            if(tp != -1 && tp && x[i] % tp == 0)
                value[i] ++;


            for(j = 0; j < n; j++)
            {
                if(i == j)
                    continue;
                if(x[j] % x[i] == 0)
                {
                    value[i]++;
                    break;
                }
            }


            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;
                if(x[i] % x[j] == 0)
                {
                    value[i]++;
                    break;
                }
            }

            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;
                if(x[j] <= 1000 && x[j] *x[j] == x[i])
                {
                    value[i]++;
                    break;
                }
            }

            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;
                if(x[j] <= 100 && x[j] *x[j]*x[j] == x[i])
                {
                    value[i]++;
                    break;
                }
            }

            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;
                if(x[j] <= 100 && x[j] *x[j]*x[j]*x[j] == x[i])
                {
                    value[i]++;
                    break;
                }
            }

            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;

                int tp = sum_digi(x[j]);

                if(tp != -1 && x[i] % tp == 0)
                {
                    value[i]++;
                    break;
                }
            }

            for(j = 0; j < n; j++)
            {
                if(j == i)
                    continue;
                int tp = nul_digi(x[j]);

               if(tp != -1 && tp != 0 && x[i] % tp == 0)
               {
                   value[i] ++;
                   break;
               }
            }
        }

        int Max = 0;
        int u = -1;

        for(i = 0; i < n; i++)
        {
            if(value[i] > Max)
            {
                Max = value[i];
            }
        }
        /*

        for(i = 0; i < n; i++)
        {
            printf("%d\n", value[i]);
        }*/

        top = 0;

        for(i = 0; i < n; i++)
        {
            if(value[i] == Max)
            {
                stack[top++] = x[i];
            }
        }

        sort(stack, stack+top);

        printf("DATA SET #%d\n", c++);


        for(i = 0; i < top; i++)
            printf("%d\n", stack[i]);

    }

    return 0;
}
