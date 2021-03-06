#include <iostream>
#include <cmath>
using namespace std;

int f[1000001];
int size, p[79001];
int num[1001];
int xin[1001];
int main()
{
    int i, j;
    int jie[10] = {1, 10, 100, 1000, 10000};
    for(i = 2; i <= 1000000; i++)
    {
        if(!f[i])
        {    
            p[size++] = i;
            for(j = i+i; j <= 1000000; j += i)
                f[j] = 1;
        }
    }
            
    int l;
    char k[1001];
    while(scanf("%s %d", &k, &l) != EOF)
    {
        if(!l && !strcmp(k, "0"))
            break;
        int len = strlen(k);

        for(i = 0; i < len; i++)
            num[i] = k[i] - '0';

        int coun = 0;
        memset(xin, 0, sizeof(xin));
        int top = 0;
        for(i = len - 1; i >= 0; i--)
        {
            xin[top] += num[i]*jie[coun];
            coun++;
            if(coun == 3)
            {
                coun = 0;
                top++;
            }
        }

        if(coun)
            top++;

        //for(i = 0; i < top; i++)
            //printf("%d\n", xin[i]);


        int flag = 0;

        for(i = 0; i < size && p[i] < l; i++)
        {
            int sum = 0;
            
            for(j = top-1; j >= 0; j--)
                sum = ( sum*1000 + xin[j] ) % p[i];
            if(sum == 0)
            {
                 flag = 1;
                 break;
            }
        }

        if(!flag)
            printf("GOOD\n");
        else
            printf("BAD %d\n", p[i]);

    }
}

